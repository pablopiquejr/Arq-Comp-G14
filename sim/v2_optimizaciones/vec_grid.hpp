//
// Created by sergio on 3/10/23.
//
#ifndef LAB_ARQUITECTURA_VEC_GRID_HPP
#define LAB_ARQUITECTURA_VEC_GRID_HPP

#include "../constants.hpp"
#include "../h_y_m_struct.hpp"
#include "vec_block.hpp"

#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

class Grid {
  public:
    // n_x, n_y, n_z
    std::vector<int> borders = {0, 0, 0};

    // PUEDE QUE CON INT NOS PASEMOS DEL RANGO Y NECESITEMOS DOUBLE
    int size_cubo;

    //std::vector<int> vertices;

    std::vector<Vec_Bloque> bloques;

    explicit Grid(longitud_y_masa & setter) : l_m{setter} {};

    longitud_y_masa l_m;

    int transform(int i, int j, int k);

    void primeros_calculos();

    void check_if_repos();

    void reposicionar_particula(Particula & particula, std::vector<double> newpos);

    std::vector<Vec_Bloque> get_adyacents(int i);

    void adyacent_subx(std::vector<int> const & coor, std::vector<Vec_Bloque> & adyacentes);
    void adyacent_x(std::vector<int> const & coor, std::vector<Vec_Bloque> & adyacentes);
    void adyacent_plusx(std::vector<int> const & coor, std::vector<Vec_Bloque> & adyacentes);

    void incremento_densidades(int & id1, int & id2);

    void choques_entre_particulas();

    void transferencia_aceleracion();

    void incremento_aceleracion(Particula & particula_i, Particula & particula_j,
                                double norma) const;

    void procesamiento_colisiones();

};
#endif  // LAB_ARQUITECTURA_VEC_GRID_HPP
