//
// Created by sergio on 3/10/23.
//
#include "grid.hpp"

// el 1.5 es 3/2
// NOTA: SE PASA DE COMPLEXIDAD POR EXCESO DE PARAMETROS
void incremento_aceleracion(Particula & particula_i, Particula & particula_j, double norma,
                            longitud_y_masa const & l_m) {
  std::vector<double> var_ac = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  double const operador_izquierda =
      15 * l_m.masa_p * 1.5 * p_s *
      std::pow(l_m.l_suavizado - std::pow(std::max(norma, std::pow(10, -12)), 0.5), 2) *
      (particula_i.densidad + particula_j.densidad - 2 * (std::pow(10, -3))) /
      (std::numbers::pi * std::pow(l_m.l_suavizado, 6) *
       std::pow(std::max(norma, std::pow(10, -12)), 0.5));
  double const operador_derecha =
      45 * 0.4 * l_m.masa_p / (std::numbers::pi * std::pow(l_m.l_suavizado, 6));
  var_ac[0]       = (particula_i.pxyz[0] - particula_j.pxyz[0]) * operador_izquierda;
  var_ac[1]       = (particula_i.pxyz[1] - particula_j.pxyz[1]) * operador_izquierda;
  var_ac[2]       = (particula_i.pxyz[2] - particula_j.pxyz[2]) * operador_izquierda;
  var_ac[3]       = (particula_j.vxyz[0] - particula_i.vxyz[0]) * operador_derecha;
  var_ac[4]       = (particula_j.vxyz[1] - particula_i.vxyz[1]) * operador_derecha;
  var_ac[m_num_5] = (particula_j.vxyz[2] - particula_i.vxyz[2]) * operador_derecha;
  var_ac[m_num_6] = (var_ac[0] + var_ac[3]) / (particula_i.densidad * particula_j.densidad);
  var_ac[m_num_7] = (var_ac[1] + var_ac[4]) / (particula_i.densidad * particula_j.densidad);
  var_ac[m_num_8] = (var_ac[2] + var_ac[m_num_5]) / (particula_i.densidad * particula_j.densidad);
  for (size_t i = 0; i < 3; ++i) {
    particula_i.a_c[i] += var_ac[i + m_num_6];
    particula_j.a_c[i] += var_ac[i + m_num_6];
  }
}

void incremento_densidades(Particula & particula_i, Particula & particula_j,
                           longitud_y_masa const & l_m) {
  double const norma = std::pow(particula_i.pxyz[0] - particula_j.pxyz[0], 2) +
                       std::pow(particula_i.pxyz[1] - particula_j.pxyz[1], 2) +
                       std::pow(particula_i.pxyz[2] - particula_j.pxyz[2], 2);
  double const h_2 = std::pow(l_m.l_suavizado, 2);
  if (norma < h_2) {
    double const incremento  = std::pow(h_2 - norma, 3);
    particula_i.densidad    += incremento;
    particula_j.densidad    += incremento;
  }
  particula_i.transformacion_densidad(l_m.l_suavizado, l_m.masa_p);
  particula_j.transformacion_densidad(l_m.l_suavizado, l_m.masa_p);
  incremento_aceleracion(particula_i, particula_j, norma, l_m);
}

void Cubo::set_grid_values() {
  borders[0] = floor((max[0] - min[0]) / l_m.l_suavizado);
  borders[1] = floor((max[1] - min[1]) / l_m.l_suavizado);
  borders[2] = floor((max[2] - min[2]) / l_m.l_suavizado);
}

void Cubo::creacion_bloques() {
  for (int i = 0; i < borders[0]; i++) {
    for (int j = 0; j < borders[1]; j++) {
      for (int k = 0; k < borders[2]; k++) {
        Bloque const bloque(i, j, k);
        bloques.push_back(bloque);
      }
    }
  }
  asignacion_inicial();
}

void Cubo::asignacion_inicial() {
  for (Particula & particula : l_m.list_of_particles) {
    particula.bpos[0]=floor((particula.pxyz[0] - min[0]) * borders[0] / (max[0] - min[0]));
    particula.bpos[1]=floor((particula.pxyz[1] - min[1]) * borders[1] / (max[1] - min[1]));
    particula.bpos[2]=floor((particula.pxyz[2] - min[2]) * borders[2] / (max[2] - min[2]));

    for (Bloque & bloque : bloques) {
      if (particula.bpos[0] == bloque.b_x && particula.bpos[1] == bloque.b_y &&
          particula.bpos[2] == bloque.b_z) {
        bloque.lista_particulas.push_back(particula);
      }
    }
  }
}

void Cubo::choques_entre_particulas() {
  // Esto tiene en cuenta consigo mismo tmb eso esta bien?
  for (Bloque & bloque : bloques) {
    for (Bloque & bloque2 : bloques) {
      if (bloque.b_x == bloque2.b_x - 1 || bloque.b_x == bloque2.b_x ||
          bloque.b_x == bloque2.b_x + 1 || bloque.b_y == bloque2.b_y - 1 ||
          bloque.b_y == bloque2.b_y || bloque.b_y == bloque2.b_y + 1 ||
          bloque.b_z == bloque2.b_z - 1 || bloque.b_z == bloque2.b_z ||
          bloque.b_z == bloque2.b_z + 1) {
        comprobar_reposicionamiento(bloque, bloque2);
      }
    }
  }
}

void Cubo::comprobar_reposicionamiento(Bloque & bloque, Bloque & bloque2) {
  for (Particula particula : bloque.lista_particulas) {
    for (Particula particula2 : bloque2.lista_particulas) {
      if (particula.identifier < particula2.identifier) {
        if (!particula.repos) {
          set_particles_coordinates(particula, bloque);
          particula.repos = true;
        }
        if (!particula2.repos) {
          set_particles_coordinates(particula2, bloque2);
          particula2.repos = true;
        }
        incremento_densidades(particula, particula2, l_m);
      }
    }
  }
}

void Cubo::set_particles_coordinates(Particula & particula, Bloque & bloque) {
  std::vector<double> newpos = {
    floor((particula.pxyz[0] - min[0]) * borders[0] / (max[0] - min[0])),
    floor((particula.pxyz[1] - min[1]) * borders[1] / (max[1] - min[1])),
    floor((particula.pxyz[2] - min[2]) * borders[2] / (max[2] - min[2]))
  };
  if (particula.bpos[0] != newpos[0] || particula.bpos[1] != newpos[1] ||
      particula.bpos[2] != newpos[2]) {
    for (int mode; mode < 3; mode++) {
      if (0 > newpos[mode]) {
        newpos[mode] = 0;
      } else if (newpos[mode]> borders[mode] - 1) {
        newpos[mode]= borders[mode] - 1;
      }
    }
    reposicionar_particula(newpos, particula, bloque);
  }
}

void Cubo::reposicionar_particula(std::vector<double> const newpos, Particula & particula,
                                  Bloque & bloque_original) {
  int counter = 0;
  for (Particula & p_extra : bloque_original.lista_particulas) {
    if ((p_extra.bpos[0] == particula.bpos[0]) && (p_extra.bpos[1] == particula.bpos[1]) &&
        (p_extra.bpos[2] == particula.bpos[2])) {
      bloque_original.lista_particulas.erase(bloque_original.lista_particulas.begin(),
                                             bloque_original.lista_particulas.begin() + counter);
      break;
    }
    counter++;
  }
  particula.bpos[0] = newpos[0];
  particula.bpos[1] = newpos[1];
  particula.bpos[2] = newpos[2];
  for (Bloque & bloque : bloques) {
    if ((bloque.b_x == particula.bpos[0]) && (bloque.b_y == particula.bpos[1]) &&
        (bloque.b_z == particula.bpos[2])) {
      bloque.lista_particulas.push_back(particula);
    }
  }
}

void Cubo::colision_limites() {
  for (Bloque & bloque : bloques) {
    if (bloque.b_x == 0) {
      bloque.colision_x_baja();
    } else if (bloque.b_x == borders[0] - 1) {
      bloque.colision_x_alta();
    } else if (bloque.b_y == 0) {
      bloque.colision_y_baja();
    } else if (bloque.b_y == borders[1] - 1) {
      bloque.colision_y_alta();
    } else if (bloque.b_z == 0) {
      bloque.colision_z_baja();
    } else if (bloque.b_z == borders[2] - 1) {
      bloque.colision_z_alta();
    } else {
      for (Particula & particula : bloque.lista_particulas) { particula.movimiento_particulas(); }
    }
  }
}
