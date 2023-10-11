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
    double calculo_sx(double nx, double xmax, double xmin);
    double calculo_sy(double nx, double xmax, double xmin);
    double calculo_sz(double nx, double xmax, double xmin);
    void colision_x1(Particula & particula, double xmin, double xmax);
    void colision_y1(Particula & particula, double ymin, double ymax);
    void colision_z1(Particula & particula, double zmin, double zmax);
    void colision_x(class particula, double xmin, double xmax,double h);
    void colision_y(class particula, double ymin, double ymax,double h);
    void colision_z(class particula, double ymin, double ymax,double h);


};
#endif  // LAB_ARQUITECTURA_BLOCK_HPP

