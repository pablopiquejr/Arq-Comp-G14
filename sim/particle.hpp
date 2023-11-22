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
    int num_particles;

    std::vector<std::array<double, 3>> pxyz;
    std::vector<std::array<double, 3>> hvxyz;
    std::vector<std::array<double, 3>> vxyz;
    std::vector<std::array<double, 3>> a_c;
    std::vector<double> densidad;
    std::vector<std::array<int, 3>> bpos;

    // Constructor que toma num_particles como parámetro
    explicit Particula(int num_p) : num_particles(num_p) {
      pxyz.resize(num_particles, {0.0, 0.0, 0.0});
      hvxyz.resize(num_particles, {0.0, 0.0, 0.0});
      vxyz.resize(num_particles, {0.0, 0.0, 0.0});
      a_c.resize(num_particles, {0.0, gravedad, 0.0});
      densidad.resize(num_particles, 0.0);
      bpos.resize(num_particles, {0, 0, 0});
    }
};

#endif
