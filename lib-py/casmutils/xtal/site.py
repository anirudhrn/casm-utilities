from . import _xtal
from . import globaldef

class Equals:

    """A wrapper class for _xtal.SiteEquals_f"""

    def __init__(self, ref_site, tol):
        """Construct Equals from Site
        or MutableSite and a given tolerance

        Parameters
        ----------
        ref_site : Site or MutableSite
        tol : double

        """
        self._SiteEquals_f = _xtal.SiteEquals_f(ref_site._pybind_value, tol)

    def __call__(self, other):
        """Overloading () operator

        Parameters
        ----------
        other : Site or MutableSite

        Returns
        -------
        bool

        """
        return self._SiteEquals_f(other._pybind_value)

class _Site:

    """Base class for both mutable and immutable Site classes.
    Defines the functions that should be common to both"""

    def __init__(self,coord,label):
        """create an instance of _xtal.Site
        as a container to access it's member
        functions

        Parameters
        ----------
        coord : np.array
        label : string

        """
        self._pybind_value = _xtal.Site(coord,label)

    def cart(self):
        """Returns cartesian coordinates of the Site

        Returns
        -------
        np.array

        """
        return self._pybind_value._cart_const()

    def frac(self, lat):
        """Returns fractional coordinates of the Site

        Parameters
        ----------
        lat : Lattice

        Returns
        -------
        np.array

        """
        return self._pybind_value._frac_const(lat)

    def label(self):
        """Returns label of atom at the Site

        Returns
        -------
        string

        """
        return self._pybind_value._label_const()

    def set_compare_method(self, method, *args):
        """Determines what strategy to use for comparing
        Sites

        Parameters
        ----------
        method : Functor class that performs the comparision
        *args : Arguments needed to construct the Functor

        """
        self._equals = method(self, *args)

    def __eq__(self, other):
        """Passes the "other" to the cuurent compare functor
        and compares it to the self and returns the evaluation

        Parameters
        ----------
        other : _Site

        Returns
        -------
        bool

        """
        if hasattr(self, '_equals') is False:
            self.set_compare_method(Equals, globaldef.tol)

        return self._equals(other)

    def __ne__(self, other):
        """Passes the "other" to the current compare functor
        and compares it to the self and returns opposite of the
        evaluation

        Parameters
        ----------
        other : _Site

        Returns
        -------
        bool

        """
        return not self==other

class Site(_Site):

    """Immutable Site Class"""

    def __init__(self, coord, label):
        """Constructor inheriting from
        parent's constructor

        Parameters
        ----------
        coord : np.array
        label : string

        """
        super().__init__(coord, label)

class MutableSite(_Site):

    """Mutable Site Class"""

    def __init__(self, coord, label):
        """Constructor inheriting from
        parent's constructor

        Parameters
        ----------
        coord : np.array
        label : string

        """
        super().__init__(coord, label)
