//
// Created by sergio on 3/10/23.
//
#ifndef LAB_ARQUITECTURA_BLOCK_HPP
#define LAB_ARQUITECTURA_BLOCK_HPP

#include "particle.hpp"

#include <cmath>
#include <iostream>

class Bloque {
  public:
    int b_x;
    int b_y;
    int b_z;
    std::vector<Particula> lista_particulas;

    Bloque(int param_x, int param_y, int param_z);

    void colision_x(int n_x);
    void colision_y(int n_y);
    void colision_z(int n_z);

    void recinto_x(int n_x);
    void recinto_y(int n_y);
    void recinto_z(int n_z);

    void colision_x_baja();
    void colision_y_baja();
    void colision_z_baja();
    void colision_x_alta();
    void colision_y_alta();
    void colision_z_alta();

};
#endif  // LAB_ARQUITECTURA_BLOCK_HPP
