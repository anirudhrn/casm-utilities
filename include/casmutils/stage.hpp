#ifndef UTILS_STAGE_HH
#define UTILS_STAGE_HH

#include "casmutils/structure.hpp"
#include "casm/symmetry/SymOp.hh"

namespace Rewrap
{
/** This class holds the information of a symmetry operation,
 * including the transformation matrix and translation vector
 */

    class SymOp
    {
        public:

            SymOp()=delete;

            /// Construct from the casm type
            SymOp(const CASM::SymOp& op): casm_symop(op){}

            /// 
            Eigen::Matrix3d matrix() const;

            ///
            Eigen::Vector3d translation() const;

            const CASM::SymOp& __get() const { return casm_symop;}

        private:

            CASM::SymOp casm_symop;
    };
}

namespace Simplicity
{
std::vector<Rewrap::SymOp> make_factor_group(const Rewrap::Structure& struc, double tol);

/// Applies the given symmetry operation to the coordinate and returs a new transformed version
Rewrap::Coordinate apply_symmetry(const Rewrap::SymOp& op, const Rewrap::Coordinate& coord);

/// Return all coordinates that are equivalent according to the provided symmetry group
std::vector<Rewrap::Coordinate> symmetrically_equivalent_coordinates(const std::vector<Rewrap::SymOp>& sym_group, const Rewrap::Coordinate& coord);
}

/* std::vector<Rewrap::Coordinate> use_factor_group(const Rewrap::Structure& struc, double tol, const Rewrap::Coordinate& coord) */
/* { */
/*     auto factor_group=make_factor_group(struc,tol); */
/*     return apply_factor_group(factor_group,coord); */
/* } */

#endif
