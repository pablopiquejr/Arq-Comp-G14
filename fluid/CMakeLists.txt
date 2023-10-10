add_executable(fluid fluid.cpp
        ../sim/particle.cpp
        ../sim/particle.hpp
        ../utest/progargs_test.cpp
        ../utest/grid_test.cpp
        ../utest/block_test.cpp
) ####### ESTABA COMO fluid .cpp ################
target_link_libraries ( fluid sim)