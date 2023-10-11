//
// Created by sergio on 3/10/23.
//
#include "particle.hpp"
#ifndef LAB_ARQUITECTURA_BLOCK_HPP
#define LAB_ARQUITECTURA_BLOCK_HPP
class Bloque {
private:
    int c_x = 0;
    int c_y = 0;
    int c_z = 0;
public:
    Bloque() = default;
    void colision_x1(Particula & particula, double xmin, double xmax);
    void colision_y1(Particula & particula, double ymin, double ymax);
    void colision_z1(Particula & particula, double zmin, double zmax);
    void collision_x(class particula, double xmin, double xmax,double h);
    void collision_y(class particula, double ymin, double ymax,double h);
    void collision_z(class particula, double ymin, double ymax,double h);


};
#endif  // LAB_ARQUITECTURA_BLOCK_HPP

