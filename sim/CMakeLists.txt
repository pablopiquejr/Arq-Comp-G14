# Add to this list all files related to sim library
add_library(sim
        progargs.hpp
        progargs.cpp
        constants.hpp
        particle.hpp
        setter.hpp
        Grid.hpp
        Grid.cpp
        Block.hpp
        Block.cpp
)
# Use this line only if you have dependencies from stim to GSL
target_link_libraries (sim PRIVATE Microsoft.GSL::GSL)
