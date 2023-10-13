//
// Created by sergio on 3/10/23.
//
#include "grid.hpp"
#include "block.hpp"
#include <list>

double Cubo::set_grid_values() {
  n_x = (x_max - x_min) / h_logitud_suavizado;
  n_y = (y_max - y_min) / h_logitud_suavizado;
  n_z = (z_max - z_min) / h_logitud_suavizado;
}

void Cubo::creacion_bloques(){
    std::list<Bloque> bloques;
    for (int i = 0;i < n_x;i++){
      for (int j=0; j < n_y; j++){
        for (int k= 0; k < n_z; k++){
          Bloque const bloque(i, j, k);
          bloques.push_back(bloque);
        }
      }
    }
};
