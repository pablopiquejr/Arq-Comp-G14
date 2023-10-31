//
// Created by sergio on 3/10/23.
//
#ifndef LAB_ARQUITECTURA_GRID_HPP
#define LAB_ARQUITECTURA_GRID_HPP

#include "block.hpp"
#include "constants.hpp"
#include "h_y_m_struct.hpp"

#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

class Cubo {
  public:
    int n_x = 0;
    int n_y = 0;
    int n_z = 0;
    std::vector<Bloque> bloques;

    explicit Cubo(longitud_y_masa & setter) : l_m{setter} {};

    longitud_y_masa l_m;

    void set_grid_values();
    void creacion_bloques();

    void set_particles_coordinates(Particula & particula) ;
    void asignacion_inicial();
    void reposicionar_particula_i(Particula &particula,Bloque  &bloque_original);
    void choques_entre_particulas();

    void colision_limites();
};
#endif  // LAB_ARQUITECTURA_GRID_HPP
