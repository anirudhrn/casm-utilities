#include <vector>
#include "casmutils/structure.hpp"
#include "casmutils/stage.hpp"

namespace Simplicity
{
std::vector<Rewrap::SymOp> make_factor_group(const Rewrap::Structure& struc, double tol)
{
    //Create empty group
    CASM::SymGroup factor_group;
    //Fill the factor group
    struc.generate_factor_group(factor_group,tol);
    assert(factor_group.size()>0);

    //Convert the casm SymGroup into vector of Rewrap::SymOp
    std::vector<Rewrap::SymOp> rewrapped_factor_group;
    for(const auto& op : factor_group)
    {
        rewrapped_factor_group.emplace_back(op);
    }

    return rewrapped_factor_group;
}

Rewrap::Coordinate apply_symmetry(const Rewrap::SymOp& op, const Rewrap::Coordinate& coord)
{
    const auto& casm_coord=coord.__get();
    const auto& casm_symop=op.__get();

    CASM::Coordinate transformed_coord=CASM::copy_apply(casm_symop, casm_coord);
    return Rewrap::Coordinate(transformed_coord);
}

std::vector<Rewrap::Coordinate> symmetrically_equivalent_coordinates(const std::vector<Rewrap::SymOp>& sym_group, const Rewrap::Coordinate& coord)
{
    std::vector<Rewrap::Coordinate> equivalent_coords;
    for(const auto& op : sym_group)
    {
        equivalent_coords.push_back(apply_symmetry(op,coord));
    }

    return equivalent_coords;
}
}
