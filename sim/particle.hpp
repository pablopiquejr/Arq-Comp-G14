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

// La estructura elegida es un objeto de vectores
class Particula {
  public:
    int num_particles;

    // La estructura es un vector de arrays, ya que no sabemos inicialmente el numero de particulas
    // con las que vamos a operar, sin embargo si sabemos que cada una tiene tres coordenadas
    std::vector<std::array<double, 3>> pxyz;
    std::vector<std::array<double, 3>> hvxyz;
    std::vector<std::array<double, 3>> vxyz;
    std::vector<std::array<double, 3>> a_c;
    // Exceptuando a la densidad que solo tiene una coordenada
    std::vector<double> densidad;
    std::vector<std::array<int, 3>> bpos;

    // Constructor que toma num_particles como parámetro, una vez sabemos de que tamaño son los
    // vectores y los valores iniciales
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
