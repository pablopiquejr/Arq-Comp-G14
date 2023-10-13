//
// Created by sergio on 3/10/23.
//
#include "grid.hpp"
#include "block.hpp"
#include <list>

double Cubo::calculo_nx() {
    double const n_x = (x_max - x_min) / h;
    return n_x;
}

double Cubo::calculo_ny() {
    double const n_y = (y_max - y_min) / h;
    return n_y;
}

double Cubo::calculo_nz() {
    double const n_z = (z_max - z_min) / h;
    return n_z;
}

void Cubo::creacion_bloques(){
    std::list<Bloque> bloques;
    for (int i = 0;i < nx;i++){
      for (int j=0; i < ny; j++){
        for (int k= 0; i < nz; k++){
          Bloque bloque(i, j, k);
          bloques.push_back(bloque);
        }
      }
    }
};
