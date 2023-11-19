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

      int size_cubo = 0;

      std::vector<Vec_Bloque> bloques;

      explicit Grid(longitud_y_masa & setter) : l_m{setter} {};

      longitud_y_masa l_m;

      void escribir_datos_iniciales();

      int transform(int i, int j, int k);

      std::vector<Vec_Bloque> get_adyacents(int i);
      void primeros_calculos();

      void check_if_repos();

      void reposicionar_particula(Particula & particula, int index, std::vector<double> newpos);

      void incremento_densidades(int & id1, int & id2);

      void choques_entre_particulas();

      void transferencia_aceleracion();

      void incremento_aceleracion(Particula & particula_i, int index1, int index2, double norma)
          const;

      void procesamiento_colisiones();

      // void write_report(int n_iteraccion);

      Grid() = default;

};
#endif  // LAB_ARQUITECTURA_VEC_GRID_HPP
