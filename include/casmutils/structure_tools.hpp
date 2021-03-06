#ifndef STRUCTURE_TOOLS_HH
#define STRUCTURE_TOOLS_HH

#include "casmutils/structure.hpp"

namespace Simplicity
{
/// Given a Structure, write out its information into a file in a vasp compatible format
void write_poscar(const Rewrap::Structure& printable, const Rewrap::fs::path& filename);

/// Given a Structure, print out its information to the given stream in a vasp compatible format
void print_poscar(const Rewrap::Structure& printable, std::ostream& outstream);

/// Return a copy of the given Structure that has been converted to its standard niggli form
Rewrap::Structure make_niggli(const Rewrap::Structure& non_niggli);

/// Modify the given Structure to standard niggli form
void make_niggli(Rewrap::Structure* non_niggli);

/// Return a Structure that is the primitive of the provided one
Rewrap::Structure make_primitive(const Rewrap::Structure& input);

/// Returns a super structure after applying a transformation matrix to the structure.
/// Applies transformation to the lattice and uses CASM::Structure::create_superstruc to fill the basis.
/// transformed_lattice =  original_lattice * transformation_matrix
Rewrap::Structure make_super_structure(const Rewrap::Structure& struc, const Eigen::Matrix3i& col_transf_mat);

/// Takes a pointer to a structure and applies deformation to that structure.
/// Deforms the lattice and keeps the basis constant in fractional space.
/// deformed_lattice = deformation_tensor * undeformed_lattice.
/// Does not remove rotation even if it exists!!!
void apply_deformation(Rewrap::Structure* struc_ptr, const Eigen::Matrix3d& deformation_tensor);
Rewrap::Structure apply_deformation(const Rewrap::Structure& struc_ptr, const Eigen::Matrix3d& deformation_tensor);

/// Takes a pointer to a structure and applies strain to that structure.
/// Input is unrolled strain in conventional metrics as defined in the mode.
/// Allowed modes are 'GL' [Green-Lagrange], 'EA' [Euler-Almansi], 'B' [Biot], or 'H' [Hencky] and throws an error if
/// the mode is not in this list. Uses functions from CASM::StrainConverter class to roll up the strain and obtain a
/// deformation tensor. Applies deformation using apply_deformation function.
void apply_strain(Rewrap::Structure* struc_ptr, const Eigen::VectorXd& unrolled_strain, const std::string& mode);
Rewrap::Structure apply_strain(const Rewrap::Structure& struc_ptr, const Eigen::VectorXd& unrolled_strain,
                               const std::string& mode);

/// Map a vector of structures onto a single reference structures, return a vector of score pairs
/// for the lattice (first) and basis (second).
std::vector<std::pair<double, double>> structure_score(const Rewrap::Structure& map_reference_struc,
                                                       const std::vector<Rewrap::Structure>& mappable_struc_vec);

/// Map a single structure onto a reference structure.
/// Returns scores for lattice (first) and basis (second) as a pair.
std::pair<double, double> structure_score(const Rewrap::Structure& map_reference_struc,
                                          const Rewrap::Structure& mappable_struc);

/// Given a structure, find all the superstructures between volumes min_vol and max_vol
std::vector<Rewrap::Structure> make_superstructures_of_volume(const Rewrap::Structure& structure, const int volume);

/// Find the index of the superstructure with the highest volume/surface_area ratio of the ones given
std::vector<Rewrap::Structure>::size_type
boxiest_structure_index(const std::vector<Rewrap::Structure>& candidate_structures);
/* const Rewrap::Structure& boxiest_structure(const std::vector<Rewrap::Structure>& candidate_structures); */

/// Find the most boxy superstructure at each volume
Rewrap::Structure make_boxiest_superstructure_of_volume(const Rewrap::Structure& structure, const int volume);
} // namespace Simplicity

#endif
