//
// Created by sergio on 3/10/23.
//
#include "particle.hpp"
#include "constants.hpp"
#ifndef LAB_ARQUITECTURA_BLOCK_HPP
#define LAB_ARQUITECTURA_BLOCK_HPP
class Bloque {
  public:
    int b_x_coordinate = 0;
    int b_y_coordinate = 0;
    int b_z_coordinate = 0;

    Bloque(int i, int i1, int i2) = default;

    // Todos estos statics creo que son porque no llamamos a las funciones como tal creo

    
    static double transformacion_densidad(Particula & particula);
    static void movimiento_particulas(Particula & particula_i);
    static void incremento_densidades(Particula & particula_i, Particula & particula_j);
    static void incremento_aceleracion(Particula & particula_i, Particula & particula_j, double norma);

    void colision_x1(Particula & particula);
    void colision_y1(Particula & particula);
    void colision_z1(Particula & particula);
    void colision_x(Particula & particula);
    void colision_y(Particula & particula);
    void colision_z(Particula & particula);
};
#endif  // LAB_ARQUITECTURA_BLOCK_HPP

