//
// Created by sergio on 3/10/23.
//
#ifndef LAB_ARQUITECTURA_BLOCK_HPP
#define LAB_ARQUITECTURA_BLOCK_HPP

#include <cmath>
#include <iostream>
#include "particle.hpp"
#include <list>

class Bloque {
  public:
    int b_x = 0;
    int b_y = 0;
    int b_z = 0;
    std::list<Particula> lista_particulas;

    Bloque(int b_x_coordinate,int b_y_coordinate,int b_z_coordinate);

};
#endif  // LAB_ARQUITECTURA_BLOCK_HPP

