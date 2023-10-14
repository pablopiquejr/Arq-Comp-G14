//
// Created by sergio on 3/10/23.
//
#ifndef LAB_ARQUITECTURA_BLOCK_HPP
#define LAB_ARQUITECTURA_BLOCK_HPP

#include "particle.hpp"

#include <cmath>
#include <iostream>
#include <list>

class Bloque {
  public:
    int b_x;
    int b_y;
    int b_z;
    std::list<Particula> lista_particulas;

    Bloque(int b_x, int b_y, int b_z);

    void colision_x_baja();
    void colision_y_baja();
    void colision_z_baja();
    void colision_x_alta();
    void colision_y_alta();
    void colision_z_alta();


};
#endif  // LAB_ARQUITECTURA_BLOCK_HPP

