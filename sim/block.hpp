//
// Created by sergio on 3/10/23.
//
#include "particle.hpp"
#include "constants.hpp"
#ifndef LAB_ARQUITECTURA_BLOCK_HPP
#define LAB_ARQUITECTURA_BLOCK_HPP
class Bloque {
private:
    int identifier = 0;
    int s_x = 0;
    int s_y = 0;
    int s_z = 0;
public:
  Bloque(int i, int i1, int i2) = default;

    // Todos estos statics creo que son porque no llamamos a las funciones como tal creo

    
    static double transformacion_densidad(Particula & particula);
    static void movimiento_particulas(Particula & particula_i);
    static void incremento_densidades(double h, Particula & particula_i, Particula & particula_j);
    static void incremento_aceleracion(Particula & particula_i, Particula & particula_j, double h,
                                       double norma, double m);

    void colision_x1(Particula & particula, double x_min, double x_max);
    void colision_y1(Particula & particula, double y_min, double y_max);
    void colision_z1(Particula & particula, double z_min, double z_max);
    void colision_x(Particula & particula, double x_min, double x_max,double h) const;
    void colision_y(Particula & particula, double y_min, double y_max,double h) const;
    void colision_z(Particula & particula, double y_min, double y_max,double h) const;


};
#endif  // LAB_ARQUITECTURA_BLOCK_HPP

