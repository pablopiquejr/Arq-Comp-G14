//
// Created by sergio on 3/10/23.
//
#include "particle.hpp"
#ifndef LAB_ARQUITECTURA_BLOCK_HPP
#define LAB_ARQUITECTURA_BLOCK_HPP
class Bloque {
private:
    int s_x = 0;
    int s_y = 0;
    int s_z = 0;
public:
    Bloque() = default;

    // Todos estos statics creo que son porque no llamamos a las funciones como tal creo

    static double calculo_sx(double nx, double xmax, double xmin);
    static double calculo_sy(double nx, double xmax, double xmin);
    static double calculo_sz(double nx, double xmax, double xmin);

    static double transformacion_densidad(double densidad, double h, double m);
    static void movimiento_particulas(Particula & particula_i);
    static void incremento_densidades(double h, Particula & particula_i, Particula & particula_j);
    static void incremento_aceleracion(Particula & particula_i, Particula & particula_j, double h,
                                       double norma, double m);

    void colision_x1(Particula & particula, double xmin, double xmax);
    void colision_y1(Particula & particula, double ymin, double ymax);
    void colision_z1(Particula & particula, double zmin, double zmax);
    void colision_x(Particula & particula, double xmin, double xmax,double h) const;
    void colision_y(Particula & particula, double ymin, double ymax,double h) const;
    void colision_z(Particula & particula, double ymin, double ymax,double h) const;


};
#endif  // LAB_ARQUITECTURA_BLOCK_HPP

