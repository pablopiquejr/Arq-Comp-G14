//
// Created by sergio on 5/10/23.
//
#ifndef LAB_ARQUITECTURA_PARTICLE_HPP
#define LAB_ARQUITECTURA_PARTICLE_HPP

#include "constants.hpp"
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

class Particula {
  public:
    std::vector<std::array<double,3>> pxyz;

    std::vector<std::array<double,3>>hvxyz;

    std::vector<std::array<double,3>>vxyz;

    std::vector<std::array<double,3>> a_c;
    std::vector<double>densidad;
                          // i, j, k
    std::vector<std::array<int,3>> bpos;

    Particula() = default;
};

#endif  // FLUID_PARTICLE_HPP
