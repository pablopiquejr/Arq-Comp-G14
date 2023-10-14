//
// Created by sergio on 3/10/23.
//
#ifndef LAB_ARQUITECTURA_GRID_HPP
#define LAB_ARQUITECTURA_GRID_HPP

#include "block.hpp"
#include "constants.hpp"
#include "particle.hpp"

#include <cmath>
#include <iostream>
#include <list>
#include <vector>

class Cubo {
  public:
    int n_x = 0;
    int n_y = 0;
    int n_z = 0;
    std::list<Bloque> bloques;

    Cubo() = default;
    void set_grid_values(double h_longitud_suavizado);
    void creacion_bloques(std::vector<Particula> const & list_of_particles);

    void set_particles_coordinates(Particula & particula) const;
    void asignacion_inicial(std::vector<Particula> const & list_of_particles);
    void choques_entre_particulas(double l_suavizado, double masa_p);

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
