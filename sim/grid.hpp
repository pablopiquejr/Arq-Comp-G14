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
    // n_x, n_y, n_z
    std::vector<int> borders = {0, 0, 0};

    std::vector<Bloque> bloques;

    explicit Cubo(longitud_y_masa & setter) : l_m{setter} {};

    longitud_y_masa l_m;

    void set_grid_values();
    void creacion_bloques();

    void set_particles_coordinates(Particula & particula, Bloque & bloque);
    void asignacion_inicial();
    void reposicionar_particula(int mode, Particula & particula, Bloque & bloque_original);
    void choques_entre_particulas();
    void comprobar_reposicionamiento(Bloque &bloque, Bloque &bloque2);
    void colision_limites();
};
#endif  // LAB_ARQUITECTURA_GRID_HPP
