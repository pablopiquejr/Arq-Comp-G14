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

    Bloque(int i, int i1, int i2) = default;

    // Todos estos statics creo que son porque no llamamos a las funciones como tal creo

    
    static double transformacion_densidad(Particula & particula);
    static void movimiento_particulas(Particula & particula_i);
    void incremento_densidades(Particula & particula_i, Particula & particula_j);
    void incremento_aceleracion(Particula & particula_i, Particula & particula_j, double norma);

};
#endif  // LAB_ARQUITECTURA_BLOCK_HPP

