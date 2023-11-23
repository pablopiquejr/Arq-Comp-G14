//
// Created by sergio on 3/10/23.
//
#ifndef LAB_ARQUITECTURA_VEC_GRID_HPP
#define LAB_ARQUITECTURA_VEC_GRID_HPP

#include "Block.hpp"
#include "constants.hpp"
#include "setter.hpp"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <utility>
#include <vector>

class Grid {
  public:

    // n_x, n_y, n_z
    std::array<int,3> borders = {0, 0, 0};

    int size_cubo = 0;

    std::vector<Vec_Bloque> bloques;

    explicit Grid(setter & setter) : l_m{setter} {};

    setter l_m;

    void escribir_datos_iniciales();

    int transform(int i, int j, int k);

    std::vector<Vec_Bloque> get_adyacents(int i);

    void primeros_calculos();

    void check_if_repos();

    void incremento_densidad(double h_2, double norma, int id1, int id2);

    void reposicionar_particula(Particula & particula, int index, std::array<int,3> newpos);

    void choques_entre_particulas();

    void incremento_aceleracion(Particula & particula, int index1, int index2, double norma) const;

    void transferencia_aceleracion();

    void procesamiento_colisiones();

    //void write_report(int n_iteraccion);

};
#endif  // LAB_ARQUITECTURA_VEC_GRID_HPP
