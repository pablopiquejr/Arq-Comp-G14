add_executable(fluid fluid.cpp
        particle.cpp
        particle.hpp
        ../progars_test.cpp
        ../grid_test.cpp
        ../block_test.cpp
) ####### ESTABA COMO fluid .cpp ################
target_link_libraries ( fluid sim)