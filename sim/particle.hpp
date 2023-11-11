//
// Created by sergio on 5/10/23.
//
#ifndef LAB_ARQUITECTURA_PARTICLE_HPP
#define LAB_ARQUITECTURA_PARTICLE_HPP

#include "constants.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

class Particula {
  public:
    std::vector<std::vector<double>> pxyz;

    std::vector<std::vector<double>>hvxyz;

    std::vector<std::vector<double>>vxyz;

    std::vector<std::vector<double>> a_c;
    std::vector<double>densidad;
                          // i, j, k
    std::vector<std::vector<int>> bpos;

    Particula() = default;
};

#endif  // FLUID_PARTICLE_HPP
