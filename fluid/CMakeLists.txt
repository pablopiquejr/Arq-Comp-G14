add_executable(fluid fluid.cpp
        particle.cpp
        particle.hpp) ####### ESTABA COMO fluid .cpp ################
target_link_libraries ( fluid sim)