//
// Created by sergio on 3/10/23.
//
#ifndef LAB_ARQUITECTURA_GRID_HPP
#define LAB_ARQUITECTURA_GRID_HPP

#include "constants.hpp"
#include <list>
#include "block.hpp"
#include "particle.hpp"
#include <iostream>
#include <cmath>
#include <vector>
class Cubo {
    public:
      int n_x = 0;
      int n_y = 0;
      int n_z = 0;
      std::list<Bloque> bloques;


    Cubo() = default;
    void set_grid_values();
    void creacion_bloques(std::vector<Particula>list_of_particles);

    void set_particles_coordinates(Particula &particula) const;
    void asignacion_inicial(std::vector<Particula>list_of_particles);
    void choques_entre_particulas();

    void transformacion_densidad(Particula & particula);
    void movimiento_particulas(Particula & particula_i);

    void colision_x1(Particula & particula, Bloque &bloque) const;
    void colision_y1(Particula & particula, Bloque &bloque) const;
    void colision_z1(Particula & particula, Bloque &bloque) const;
    void colision_x(Particula & particula, Bloque &bloque) const;
    void colision_y(Particula & particula, Bloque &bloque) const;
    void colision_z(Particula & particula, Bloque &bloque) const;

};
#endif  // LAB_ARQUITECTURA_GRID_HPP
