#include <casm/clex/ConfigMapping.hh>
#include <casm/clex/PrimClex.hh>
#include <casm/crystallography/Niggli.hh>
#include <casm/crystallography/SuperlatticeEnumerator.hh>
#include <casm/crystallography/io/VaspIO.hh>
#include <casm/strain/StrainConverter.hh>
#include <casmutils/exceptions.hpp>
#include <casmutils/misc.hpp>
#include <casmutils/xtal/lattice.hpp>
#include <casmutils/xtal/structure_tools.hpp>
#include <fstream>

namespace
{
// surface area of a given lattice
double lattice_surface_area(const rewrap::Lattice& lat)
{
    Eigen::Vector3d a = lat[0];
    Eigen::Vector3d b = lat[1];
    Eigen::Vector3d c = lat[2];

    double ab = a.cross(b).norm();
    double bc = b.cross(c).norm();
    double ca = c.cross(b).norm();

    return std::abs(ab) + std::abs(bc) + std::abs(ca);
}

// score for determining level of boxiness, borrowed from John Goiri
double boxy_score(const rewrap::Lattice& lat)
{
    // Less surface area per volume means more boxy
    // i.e. more volume per surface area means more boxy
    return std::abs(lat.volume()) / lattice_surface_area(lat);
}
} // namespace

namespace simplicity
{
rewrap::Structure make_primitive(const rewrap::Structure& input)
{
    throw except::NotImplemented();
    /* const rewrap::CasmStructure& casted_input(input); */
    /* rewrap::CasmStructure true_prim; */
    /* //CasmStructure fills up true_prim when you call is_primitive */
    /* bool is_prim = casted_input.is_primitive(true_prim); */
    /* return true_prim; */
}

rewrap::Structure make_niggli(const rewrap::Structure& non_niggli)
{
    throw except::NotImplemented();
    /* rewrap::CasmStructure niggli = non_niggli; */
    /* CASM::Lattice lat_niggli = CASM::xtal::niggli(non_niggli.lattice(), CASM::TOL); */
    /* niggli.set_lattice(lat_niggli, CASM::CART); */
    /* return niggli; */
}

void make_niggli(rewrap::Structure* non_niggli)
{
    throw except::NotImplemented();
    /* CASM::Lattice lat_niggli = CASM::xtal::niggli(non_niggli->lattice(), CASM::TOL); */
    /* non_niggli->set_lattice(lat_niggli, CASM::CART); */
    /* return; */
}

void print_poscar(const rewrap::Structure& printable, std::ostream& outstream)
{
    throw except::NotImplemented();
    /* CASM::VaspIO::PrintPOSCAR p(printable); */
    /* p.sort(); */
    /* p.print(outstream); */
    return;
}

void write_poscar(const rewrap::Structure& printable, const rewrap::fs::path& filename)
{
    std::ofstream file_out(filename.string());
    print_poscar(printable, file_out);
    file_out.close();
    return;
}

rewrap::Structure make_super_structure(const rewrap::Structure& struc, const Eigen::Matrix3i& col_transf_mat)
{
    throw except::NotImplemented();
    /* auto lattice_mat = struc.lattice().lat_column_mat(); */
    /* // had to cast the transformation matrix to double as Eigen does not allow mixing matrix types */
    /* CASM::Lattice suplat(lattice_mat * col_transf_mat.cast<double>()); */
    /* return struc.create_superstruc(suplat); */
}

void apply_deformation(rewrap::Structure* struc_ptr, const Eigen::Matrix3d& deformation_tensor)
{
    throw except::NotImplemented();
    /* CASM::Lattice strained_lattice(deformation_tensor * struc_ptr->lattice().lat_column_mat()); */
    /* struc_ptr->set_lattice(strained_lattice, CASM::FRAC); */
    /* return; */
}

rewrap::Structure apply_deformation(const rewrap::Structure& struc_ptr, const Eigen::Matrix3d& deformation_tensor)
{
    rewrap::Structure copy_struc(struc_ptr);
    apply_deformation(&copy_struc, deformation_tensor);
    return copy_struc;
}

void apply_strain(rewrap::Structure* struc_ptr, const Eigen::VectorXd& unrolled_strain, const std::string& mode)
{
    std::set<std::string> allowed_strain_metrics = {"GL", "B", "H", "EA"};
    if (allowed_strain_metrics.count(mode))
    {
        CASM::StrainConverter converter(mode);
        auto strain_tensor = converter.rollup_E(unrolled_strain);
        auto deformation_tensor = converter.strain_metric_to_F(strain_tensor);
        apply_deformation(struc_ptr, deformation_tensor);
    }
    else
    {
        throw except::UserInputMangle("Unrecognized mode. Allowed strain metrics modes are GL, B, H and EA");
    }
    return;
}

rewrap::Structure apply_strain(const rewrap::Structure& struc_ptr, const Eigen::VectorXd& unrolled_strain,
                               const std::string& mode)
{
    rewrap::Structure copy_struc(struc_ptr);
    apply_strain(&copy_struc, unrolled_strain, mode);
    return copy_struc;
}

std::vector<std::pair<double, double>> structure_score(const rewrap::Structure& map_reference_struc,
                                                       const std::vector<rewrap::Structure>& mappable_struc_vec)
{
    throw except::NotImplemented();
    /* for (const auto& struc : mappable_struc_vec) */
    /* { */
    /*     if (struc.basis.size() != map_reference_struc.basis.size()) */
    /*     { */
    /*         throw except::BasisMismatch(); */
    /*     } */
    /* } */

    /* // get prim and make PrimClex */
    /* auto ref_prim = CASM::Structure(make_primitive(map_reference_struc)); */
    /* auto pclex = extend::quiet_primclex(ref_prim); */

    /* // mapping setup */
    /* int options = 2;      // robust mapping */
    /* double vol_tol = 0.5; // not used */
    /* double weight = 0.5;  // not used */
    /* CASM::ConfigMapper configmapper(pclex, weight, vol_tol, options, CASM::TOL); */

    /* CASM::jsonParser out;          // mapping output */
    /* std::string name;              // not used */
    /* std::vector<CASM::Index> best; // not used */
    /* Eigen::Matrix3d cart_op;       // not used */
    /* bool update = false; */

    /* std::vector<std::pair<double, double>> all_scores; */
    /* for (const auto& struc : mappable_struc_vec) */
    /* { */
    /*     // map it */
    /*     rewrap::Structure mappable_copy(struc); // can't be const, make copy */
    /*     configmapper.import_structure_occupation(mappable_copy, name, out, best, cart_op, update); */
    /*     double basis = out["best_mapping"]["basis_deformation"].get<double>(); */
    /*     double lattice = out["best_mapping"]["lattice_deformation"].get<double>(); */
    /*     all_scores.emplace_back(lattice, basis); */
    /* } */

    /* return all_scores; */
}

std::pair<double, double> structure_score(const rewrap::Structure& map_reference_struc,
                                          const rewrap::Structure& mappable_struc)
{
    std::vector<rewrap::Structure> one = {mappable_struc};
    // just calls vector version of function
    return structure_score(map_reference_struc, one).back();
}

// Finds the superstructure with the highest volume/surface_area
// Assuming that the input has structures of same volume
std::vector<rewrap::Structure>::size_type
boxiest_structure_index(const std::vector<rewrap::Structure>& candidate_structures)
{
    // TODO: throw exception on empty vector
    double running_score = 0;
    std::vector<rewrap::Structure>::size_type ix = 0;
    std::vector<rewrap::Structure>::size_type best_ix = ix;
    for (const auto& scel : candidate_structures)
    {
        double candidate_score = boxy_score(scel.lattice());
        if (candidate_score > running_score)
        {
            running_score = candidate_score;
            best_ix = ix;
        }
        ++ix;
    }
    return best_ix;
}

// Find the boxiest superstructure per volume for range of volumes
rewrap::Structure make_boxiest_superstructure_of_volume(const rewrap::Structure& structure, const int volume)
{
    std::vector<rewrap::Structure> same_vol_scels = make_superstructures_of_volume(structure, volume);
    return same_vol_scels[boxiest_structure_index(same_vol_scels)];
}

std::vector<rewrap::Structure> make_superstructures_of_volume(const rewrap::Structure& structure, const int volume)
{
    std::vector<rewrap::Structure> all_superstructures;
    /* CASM::xtal::ScelEnumProps enum_props(volume, volume+1); */
    /* CASM::xtal::SuperlatticeEnumerator lat_enumerator(structure.lattice(), enum_props, CASM::TOL); */

    /* for (const auto& lat : lat_enumerator) */
    /* { */
    /*     rewrap::Structure super = structure.create_superstruc(lat); */
    /*     simplicity::make_niggli(&super); */
    /*     all_superstructures.emplace_back(std::move(super)); */
    /* } */

    throw except::NotImplemented();

    return all_superstructures;
}
} // namespace simplicity