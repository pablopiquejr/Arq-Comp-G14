//
// Created by sergio on 4/11/23.
//

#ifndef LAB_ARQUITECTURA_VEC_BLOCK_HPP
#define LAB_ARQUITECTURA_VEC_BLOCK_HPP

  #include "./sim/particle.hpp"

  #include <cmath>
  #include <iostream>

class Vec_Bloque {
  public:
    std::vector<int> lista_particulas;

    Vec_Bloque() = default;

    std::vector<int>adyacentes;

    int b_x = 0;
    int b_y = 0;
    int b_z = 0;

    void threeD_values(int identifier, std::vector<int> borders);

    void colision_x(int n_x, Particula & particula);
    void colision_y(int n_y, Particula & particula);
    void colision_z(int n_z, Particula & particula);

    void recinto_x(int n_x, Particula & particula);
    void recinto_y(int n_y, Particula & particula);
    void recinto_z(int n_z, Particula & particula);
};


#endif  // LAB_ARQUITECTURA_VEC_BLOCK_HPP
