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
#include <vector>

class Cubo {
  public:
    int n_x = 0;
    int n_y = 0;
    int n_z = 0;
    std::vector<Bloque> bloques;

    explicit Cubo(longitud_y_masa setter):l_m{setter}{};

    longitud_y_masa const l_m;

    void set_grid_values();
    void creacion_bloques();

    void set_particles_coordinates(Particula & particula) const;
    void asignacion_inicial();
    void choques_entre_particulas();

    void movimiento_particulas(Particula & particula_i);
    void colision_limites();
    void colision_x1(Particula & particula, Bloque & bloque) const;
    void colision_y1(Particula & particula, Bloque & bloque) const;
    void colision_z1(Particula & particula, Bloque & bloque) const;
    void colision_x(Particula & particula, Bloque & bloque) const;
    void colision_y(Particula & particula, Bloque & bloque) const;
    void colision_z(Particula & particula, Bloque & bloque) const;
};
#endif  // LAB_ARQUITECTURA_GRID_HPP
