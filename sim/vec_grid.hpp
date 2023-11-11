//
// Created by sergio on 3/10/23.
//
#ifndef LAB_ARQUITECTURA_VEC_GRID_HPP
#define LAB_ARQUITECTURA_VEC_GRID_HPP

#include "constants.hpp"
#include "h_y_m_struct.hpp"
#include "vec_block.hpp"

#include <cmath>
#include <iostream>
#include <utility>
#include <vector>


class Grid {
  public:
    // n_x, n_y, n_z
    std::vector<int> borders = {0, 0, 0};

    int size_cubo;

    std::vector<Vec_Bloque> bloques;

    explicit Grid(longitud_y_masa & setter) : l_m{setter} {};

    longitud_y_masa l_m;

    int transform(int i, int j, int k);

    void get_adyacents_op(int i, Vec_Bloque &bloque);

    void primeros_calculos();

    void check_if_repos();

    std::vector<Vec_Bloque> get_adyacents(int i);

    void reposicionar_particula(Particula & particula, std::vector<double> newpos);

    void incremento_densidades(int & id1, int & id2);

    void choques_entre_particulas();

    void transferencia_aceleracion();

    void incremento_aceleracion(Particula & particula_i, Particula & particula_j,
                                double norma) const;

    void procesamiento_colisiones();

    void write_report(int n_iteraccion);

};
#endif  // LAB_ARQUITECTURA_VEC_GRID_HPP
