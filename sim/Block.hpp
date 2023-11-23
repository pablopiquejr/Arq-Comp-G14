//
// Created by sergio on 4/11/23.
//

#ifndef LAB_ARQUITECTURA_VEC_BLOCK_HPP
#define LAB_ARQUITECTURA_VEC_BLOCK_HPP

#include "../sim/particle.hpp"

#include <cmath>
#include <iostream>

// Objeto Bloque, usado para saber que particulas contiene, y con cuales colisionan
class Vec_Bloque {
  public:
    Vec_Bloque() = default;

    // Lista de sus particulas
    std::vector<int> lista_particulas;
    // Lista de sus bloques adyacentes
    std::vector<int> adyacentes;
    // Posicion del Bloque, se le da valor en grid.cpp
    int b_x = 0;
    int b_y = 0;
    int b_z = 0;
    // Función para pasar de valor unidimensional a tridimensional
    void threeD_values(int identifier, std::array<int, 3> borders);
    // Funciones para tratar colisiones con diferentes ejes (mas efectivo que hacer una funcion
    // única que dependa de un paramero que sea 0(x), 1(y) o 2(z))
    void colision_x(int n_x, Particula & particula);
    void colision_y(int n_y, Particula & particula);
    void colision_z(int n_z, Particula & particula);
    // Funciones para la colision con los limites del recinto, está separado por coordenadas por la
    // misma razón que la anterior
    void recinto_x(int n_x, Particula & particula);
    void recinto_y(int n_y, Particula & particula);
    void recinto_z(int n_z, Particula & particula);
};

#endif  // LAB_ARQUITECTURA_VEC_BLOCK_HPP
