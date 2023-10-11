//
// Created by sergio on 3/10/23.
//
double calculo_nx(double xmax, double xmin, double h) {
    double const n_x = (xmax - xmin) / h;
    return n_x;
}

double calculo_ny(double h, double ymax, double ymin) {
    double const n_y = (ymax - ymin) / h;
    return n_y;
}

double calculo_nz(double h, double zmax, double zmin) {
    double const n_z = (zmax - zmin) / h;
    return n_z;
}

#include "progargs.hpp"
