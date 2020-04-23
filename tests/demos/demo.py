import casmutils as cu
import numpy as np
import matplotlib.pyplot as plt
import glob
import os
import json

def main():
    a=2.7;
    fcc_mat=np.array([[0,a,a],[a,0,a],[a,a,0]])
    fcc_lat=cu.xtal.Lattice(*fcc_mat)

    print(fcc_lat)

    c=cu.xtal.Coordinate([0,0,0])
    s=cu.xtal.Site(c,"Ni")
    basis=[s]

    fcc_prim=cu.xtal.Structure(fcc_lat,basis)
    print(fcc_prim)

    prim_to_conventional_mat=np.array([[-1,1,1],[1,-1,1],[1,1,-1]])
    fcc_conventional=cu.xtal.make_superstructure(fcc_prim,prim_to_conventional_mat)
    print(fcc_conventional)

    ##########################################################
    hcp_stack=cu.xtal.Structure.from_poscar("./Mg-mush/basal/testing.base/final_slab.vasp")
    print(hcp_stack)

    hcp_prim=cu.xtal.make_primitive(hcp_stack)
    print(hcp_prim)

    #########################################################
    hcp_factor_group=cu.xtal.make_factor_group(hcp_prim,1e-8)
    for op in hcp_factor_group:
        print(op)
        print("------------------------")
    print(f"{len(hcp_factor_group)} total operations")

    fcc_point_group=cu.xtal.make_point_group(fcc_prim.lattice(),1e-8)
    for op in fcc_point_group:
        print(op)
        print("------------------------")
    print(f"{len(fcc_point_group)} total operations")

    #########################################################
    with open("./Mg-mush/basal/testing.shift/record.json") as f:
        shift_record = json.load(f)

    pos_paths=[os.path.join("Mg-mush/basal",p,"POSCAR") for p in shift_record["path"]]
    pos_paths.sort()
    pos_ix=np.arange(len(pos_paths))
    shift_coords=np.array([(x,y) for x,y in zip(shift_record["x_cart"],shift_record["y_cart"])])
    shifted_structures=[cu.xtal.Structure.from_poscar(p) for p in pos_paths]

    map_strategy=cu.mapping.structure.MappingInput(use_crystal_symmetry=True,k_best_maps=0,min_cost=1e-10)
    good_maps=len(shifted_structures)*[None]
    for gm_ix,ref_s in enumerate(shifted_structures):
        map_to_ref=cu.mapping.structure.StructureMapper(ref_s,map_strategy)
        good_map_indexes=[ix for ix,s in enumerate(shifted_structures) if len(map_to_ref(s))>0]
        print(f"{gm_ix} of {len(shifted_structures)}, last map: {good_map_indexes}")
        good_maps[gm_ix]=good_map_indexes

    maps_str=[str(gm) for gm in good_maps]
    unique_map_str=[m for i, m in enumerate(maps_str) if i == maps_str.index(m)]
    colors=np.arange(0,1,1/len(unique_map_str))
    color_map={m:c for m,c in zip(unique_map_str,colors)}
    plot_color_vals=[color_map[s] for s in maps_str]

    fig=plt.figure(1)
    ax=fig.add_subplot('111')
    ax.set_aspect('equal')

    for i in range(-1,2):
        for j in range(-1,2):
            periodic_shift=hcp_stack.lattice().a()*i+hcp_stack.lattice().b()*j
            x=shift_coords[:,0]+periodic_shift[0]
            y=shift_coords[:,1]+periodic_shift[1]
            ax.scatter(x,y,c=plot_color_vals)

    fig=plt.figure(2)
    ax=fig.add_subplot('111')
    ax.set_aspect('equal')
    ax.scatter(shift_coords[:,0],shift_coords[:,1],c=plot_color_vals)

    plt.show()


if __name__=="__main__":
    main()
