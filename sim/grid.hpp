//
// Created by sergio on 3/10/23.
//

#ifndef LAB_ARQUITECTURA_GRID_HPP
#define LAB_ARQUITECTURA_GRID_HPP
#include "constants.hpp"

class Cubo {
    public:
      static int n_x = 0;
      static int n_y = 0;
      static int n_z = 0;

    Cubo() = default;
    static double set_grid_values();
    void creacion_bloques();

};
#endif  // LAB_ARQUITECTURA_GRID_HPP
