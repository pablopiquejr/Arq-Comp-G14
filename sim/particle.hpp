//
// Created by sergio on 5/10/23.
//
#ifndef LAB_ARQUITECTURA_PARTICLE_HPP
#define LAB_ARQUITECTURA_PARTICLE_HPP

#include <iostream>
#include "constants.hpp"
#include <fstream>
#include <vector>
#include <cmath>

class Particula{
  public:
    double identifier = 0;
    double px = 0;
    double py = 0;
    double pz = 0;
    double hvx = 0;
    double hvy = 0;
    double hvz = 0;
    double vx = 0;
    double vy = 0;
    double vz = 0;
    std::vector<double> a_c = {0,gravedad,0};
    double densidad = 0;
    int i=0;
    int j=0;
    int k=0;

    Particula() = default;
    void printinfo(int counter) const;
    void set_particles_data(std::ifstream & file, double id);
    void transformacion_densidad();
    void movimiento_particulas();
    [[nodiscard]] std::string particle_write() const;
};

#endif  // FLUID_PARTICLE_HPP
