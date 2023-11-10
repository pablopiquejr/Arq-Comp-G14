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

    Vec_Bloque()=default;

    std::vector<Vec_Bloque>adyacentes;

    int b_x = 0;
    int b_y = 0;
    int b_z = 0;

    void threeD_values(int identifier,  std::vector<int> borders);

    void colision_x(int n_x, std::vector<Particula> &Lista_b);
    void colision_y(int n_y, std::vector<Particula> &Lista_b);
    void colision_z(int n_z, std::vector<Particula> &Lista_b);

    void recinto_x(int n_x, std::vector<Particula> &Lista_b);
    void recinto_y(int n_y, std::vector<Particula> &Lista_b);
    void recinto_z(int n_z, std::vector<Particula> &Lista_b);

    void colision_x_(int n_x, std::vector<Particula> &Lista_b);
    void colision_y_(int n_z, std::vector<Particula> &Lista_b);
    void colision_z_(int n_z, std::vector<Particula> &Lista_b);

};


#endif  // LAB_ARQUITECTURA_VEC_BLOCK_HPP
