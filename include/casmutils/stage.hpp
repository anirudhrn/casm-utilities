#ifndef UTILS_STAGE_HH
#define UTILS_STAGE_HH

#include "casmutils/definitions.hpp"
#include "casmutils/structure.hpp"

namespace SpecializedEnumeration
{

    std::vector<int>& next_permutation(std::vector<int>* configuration_occupation);


/**
 * This class uses brute force to enumerate SQS structures.
 */

class BruteforceBinarySQS
{
    class Supercell;
    class Configuration;

public:
    typedef std::vector<std::pair<std::string, int>> SpeciesRatio;
    typedef std::vector<int> ConfigurationBits;
    /// Initialize with the primitive structure (must be binary), the ratio of A/B atoms int the SQS,
    /// and a scaling factor (if scaling factor=1 then A+B=number of atoms in SQS)
    BruteforceBinarySQS(const Rewrap::Structure& prim,  SpeciesRatio species_ratio, int scaling_factor);

    //TODO: pass bspecs and clexulator paths?
    Rewrap::Structure generate_SQS() const;

private:

    Rewrap::Structure m_prim;
    SpeciesRatio m_species_ratio;
    int m_scaling_factor;
    
    std::vector<std::unique_ptr<Supercell>> m_all_supercells_of_volume;
    ConfigurationBits m_configuration_occupation;
    std::pair<int,ConfigurationBits> m_scel_index_to_best_configuration_occupation;

    ///Throws exception if the desired volume is not compatible with the species composition
    /* void _throw_if_volume_not_composition_compatible() const; */

    ///Throws excpetion if the declared species is not part of the primitive cell
    void _throw_if_species_not_in_prim() const;

    ///Throws exception of the primitive cell is not a binary structure
    void _throws_if_prim_not_binary() const;

    ///Enumerate all supercells of the specified volume
    std::vector<Supercell> _enumerate_all_supercells(int volume) const;

    std::vector<Configuration> _enumrate_all_configurations(const Supercell& supercell);
};

} // namespace SpecializedEnumeration
#endif
