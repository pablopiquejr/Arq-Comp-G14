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
    double identifier       = 0;
    // Ha sido reposicionada
    bool repos= false;
    std::vector<double> pxyz = {0,0,0};

    std::vector<double> hvxyz = {0,0,0};

    std::vector<double> vxyz = {0,0,0};

    std::vector<double> a_c = {0, gravedad, 0};
    double densidad         = 0;
                          // i, j, k
    std::vector<int> bpos = {0,0,0};

    Particula() = default;
    void printinfo() const;
    void set_particles_data(std::ifstream & file, double id);
    void transformacion_densidad(double h_logitud_suavizado, double masa_p);
    void movimiento_particulas();
    [[nodiscard]] std::vector<float> particle_write() const;
};

#endif  // FLUID_PARTICLE_HPP
