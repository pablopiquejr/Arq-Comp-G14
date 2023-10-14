//
// Created by sergio on 3/10/23.
//
#ifndef LAB_ARQUITECTURA_BLOCK_HPP
#define LAB_ARQUITECTURA_BLOCK_HPP

#include <cmath>
#include <iostream>
#include "particle.hpp"

class Bloque {
  public:
    int b_x_coordinate = 0;
    int b_y_coordinate = 0;
    int b_z_coordinate = 0;
    std::list<Particula> lista_particulas;

    Bloque(int b_x_coordinate,int b_y_coordinate,int b_z_coordinate);

    // Todos estos statics creo que son porque no llamamos a las funciones como tal creo

    
    static void transformacion_densidad(Particula & particula);
    static void movimiento_particulas(Particula & particula_i);

};
#endif  // LAB_ARQUITECTURA_BLOCK_HPP

