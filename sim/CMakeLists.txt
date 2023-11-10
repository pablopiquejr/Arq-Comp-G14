# Add to this list all files related to sim library
add_library(sim
        progargs.hpp
        progargs.cpp
        constants.hpp
        particle.cpp
        particle.hpp
        h_y_m_struct.hpp
        vec_grid.hpp
        vec_grid.cpp
        vec_block.hpp
        vec_block.cpp
)
# Use this line only if you have dependencies from stim to GSL
target_link_libraries (sim PRIVATE Microsoft.GSL::GSL)