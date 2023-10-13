//
// Created by sergio on 3/10/23.
//

#ifndef LAB_ARQUITECTURA_GRID_HPP
#define LAB_ARQUITECTURA_GRID_HPP
#include "constants.hpp"

class Cubo {
    public:
        int nx = calculo_nx(double x_max, double x_min, double h);
        int ny =  calculo_ny(double y_max, double y_min, double h);
        int nz =  calculo_nz(double z_max, double z_min, double h);

    Cubo() = default;
    double calculo_nx(double x_max, double x_min, double h);
    double calculo_ny(double y_max, double y_min, double h);
    double calculo_nz(double z_max, double z_min, double h);
    void creacion_bloques();

};
#endif  // LAB_ARQUITECTURA_GRID_HPP
