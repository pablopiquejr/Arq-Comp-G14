//
// Created by sergio on 3/10/23.
//
#include "grid.hpp"

// el 1.5 es 3/2
void Cubo::incremento_aceleracion(Particula & particula_i, Particula & particula_j, double norma) {
  std::vector<double> var_ac = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  double dist                = std::pow(std::max(norma, std::pow(10, -12)), 0.5);
  double const operador_izquierda =
      (15 * l_m.masa_p * 1.5 * p_s * std::pow(l_m.l_suavizado - dist, 2) *
       (particula_i.densidad + particula_j.densidad - 2 * p_densidad)) /
      (std::numbers::pi * std::pow(l_m.l_suavizado, 6) * dist);
  double const operador_derecha =
      45 * u_viscosidad * l_m.masa_p / (std::numbers::pi * std::pow(l_m.l_suavizado, 6));
  for (int i = 0; i < 3; ++i){
    var_ac[i] = (particula_i.pxyz[i] - particula_j.pxyz[i]) * operador_izquierda;
  }
  for (int i = 0; i < 3; ++i){
    var_ac[i+3] = (particula_j.vxyz[i] - particula_i.vxyz[i]) * operador_derecha;
  }
  var_ac[6] = (var_ac[0] + var_ac[3]) / (particula_i.densidad * particula_j.densidad);
  var_ac[7] = (var_ac[1] + var_ac[4]) / (particula_i.densidad * particula_j.densidad);
  var_ac[8] = (var_ac[2] + var_ac[m_num_5]) / (particula_i.densidad * particula_j.densidad);
  for (size_t i = 0; i < 3; ++i) {
    particula_i.a_c[i] += var_ac[i + m_num_6];
    particula_j.a_c[i] += var_ac[i + m_num_6];
  }
}

void Cubo::incremento_densidades(Particula & particula_i, Particula & particula_j) {
  double const norma = std::pow(particula_j.pxyz[0] - particula_i.pxyz[0], 2) +
                       std::pow(particula_j.pxyz[1] - particula_i.pxyz[1], 2) +
                       std::pow(particula_j.pxyz[2] - particula_i.pxyz[2], 2);
  double const h_2 = std::pow(l_m.l_suavizado, 2);
  if (norma < h_2) {
    double const incremento  = std::pow(h_2 - norma, 3);
    particula_i.densidad    += incremento;
    particula_j.densidad    += incremento;
  }
}


void Cubo::transferencia_aceleracion() {
  for (Bloque & bloque : bloques) {
    for (Bloque & bloque2 : bloques) {
      if (((bloque.b_x == bloque2.b_x + 1 || bloque.b_x == bloque2.b_x - 1 ||
            bloque.b_x == bloque2.b_x)) &&
          (bloque.b_y == bloque2.b_y + 1 || bloque.b_y == bloque2.b_y - 1 ||
           bloque.b_y == bloque2.b_y) &&
          (bloque.b_z == bloque2.b_z + 1 || bloque.b_z == bloque2.b_z - 1 ||
           bloque.b_z == bloque2.b_z)) {
        for (Particula & particula : bloque.lista_particulas) {
          for (Particula & particula2 : bloque2.lista_particulas) {
            if (particula.identifier < particula2.identifier) {
              double const norma = std::pow(particula2.pxyz[0] - particula.pxyz[0], 2) +
                                   std::pow(particula2.pxyz[1] - particula.pxyz[1], 2) +
                                   std::pow(particula2.pxyz[2] - particula.pxyz[2], 2);
              if (norma < (l_m.l_suavizado * l_m.l_suavizado)) {
                incremento_aceleracion(particula, particula2, norma);
              }
            }
          }
        }
      }
    }
  }
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
    particula.bpos[0] = floor((particula.pxyz[0] - min[0]) * borders[0] / (max[0] - min[0]));
    particula.bpos[1] = floor((particula.pxyz[1] - min[1]) * borders[1] / (max[1] - min[1]));
    particula.bpos[2] = floor((particula.pxyz[2] - min[2]) * borders[2] / (max[2] - min[2]));

    for (int pos = 0; pos < 3; pos++) {
      if (0 > particula.bpos[pos]) {
        particula.bpos[pos] = 0;
      } else if (particula.bpos[pos] > borders[pos] - 1) {
        particula.bpos[pos] = borders[pos] - 1;
      }
    }

    for (Bloque & bloque : bloques) {
      if (particula.bpos[0] == bloque.b_x && particula.bpos[1] == bloque.b_y &&
          particula.bpos[2] == bloque.b_z) {
        bloque.lista_particulas.push_back(particula);
        break;
      }
    }
  }
}

void Cubo::choques_entre_particulas() {
  // Esto tiene en cuenta consigo mismo tmb eso esta bien?
  // BTW SI LO HACEMOS COMO [0][0][0], podemos hacerlo en un único bucle creo
  for (Bloque & bloque : bloques) {
    for (Bloque & bloque2 : bloques) {
      // ESTA MAL, b2 va a volver a colisionar con los que ya habia colisionado antes
      // además esto recorre todos los bloques (4000+) y solo nos interesan max 26
      if (((bloque.b_x == bloque2.b_x + 1 || bloque.b_x == bloque2.b_x - 1 ||
            bloque.b_x == bloque2.b_x)) &&
          (bloque.b_y == bloque2.b_y + 1 || bloque.b_y == bloque2.b_y - 1 ||
           bloque.b_y == bloque2.b_y) &&
          (bloque.b_z == bloque2.b_z + 1 || bloque.b_z == bloque2.b_z - 1 ||
           bloque.b_z == bloque2.b_z)) {
        comprobar_reposicionamiento(bloque, bloque2);
      }
    }
    for (Particula & particula : bloque.lista_particulas) {
      particula.transformacion_densidad(l_m.l_suavizado, l_m.masa_p);
    }
  }
  transferencia_aceleracion();
}

void Cubo::comprobar_reposicionamiento(Bloque & bloque, Bloque & bloque2) {
  for (Particula & particula : bloque.lista_particulas) {
    for (Particula & particula2 : bloque2.lista_particulas) {
      if (particula.identifier < particula2.identifier) {
        incremento_densidades(particula, particula2);
      }
    }
  }
}

void Cubo::repos_particulas() {
  for (Bloque &bloque: bloques){
    for (Particula &particula: bloque.lista_particulas){
      set_particles_coordinates(particula, bloque);
      particula.densidad = 0;
      particula.a_c[0] = 0;
      particula.a_c[1] = gravedad;
      particula.a_c[2] = 0;
    }
    bloque.lista_particulas.erase(
        std::remove_if(
            bloque.lista_particulas.begin(),
            bloque.lista_particulas.end(),
            [](const Particula &particula) { return particula.eliminada; }),
        bloque.lista_particulas.end()
    );
  }
}

void Cubo::set_particles_coordinates(Particula & particula, Bloque & bloque) {
  std::vector<double> newpos = {
    floor((particula.pxyz[0] - min[0]) * borders[0] / (max[0] - min[0])),
    floor((particula.pxyz[1] - min[1]) * borders[1] / (max[1] - min[1])),
    floor((particula.pxyz[2] - min[2]) * borders[2] / (max[2] - min[2]))};
  for (int pos = 0; pos < 3; pos++) {
    if (0 > newpos[pos]) {
      newpos[pos] = 0;
    } else if (newpos[pos] > borders[pos] - 1) {
      newpos[pos] = borders[pos] - 1;
    }
  }
  if (particula.bpos[0] != newpos[0] || particula.bpos[1] != newpos[1] ||
      particula.bpos[2] != newpos[2]) {
    particula.bpos[0] = newpos[0];
    particula.bpos[1] = newpos[1];
    particula.bpos[2] = newpos[2];
    reposicionar_particula(particula, bloque);
  }
}

void Cubo::reposicionar_particula(Particula & particula,
                                  Bloque & bloque_original) {
  Particula dummy = particula;
  for (Particula & p_extra : bloque_original.lista_particulas) {
    if (p_extra.identifier == particula.identifier) {
      particula.eliminada = true;
      break;
    }
  }
  for (Bloque & bloque : bloques) {
    if ((bloque.b_x == dummy.bpos[0]) && (bloque.b_y == dummy.bpos[1]) &&
        (bloque.b_z == dummy.bpos[2])) {
      bloque.lista_particulas.push_back(particula);
      break;
    }
  }
}

size_t partition(std::vector<Particula> & particles, size_t low, size_t high) {
  int pivot = particles[high].identifier;
  size_t i  = low - 1;

  for (size_t j = low; j < high; j++) {
    if (particles[j].identifier < pivot) {
      i++;
      std::swap(particles[i], particles[j]);
    }
  }

  std::swap(particles[i + 1], particles[high]);
  return i + 1;
}

// QuickSort implementation
void quickSort(std::vector<Particula> & particles, size_t low, size_t high) {
  if (low < high) {
    size_t pivotIndex = partition(particles, low, high);

    if (pivotIndex > 0) { quickSort(particles, low, pivotIndex - 1); }
    quickSort(particles, pivotIndex + 1, high);
  }
}

longitud_y_masa Cubo::actualizar_lista() {
  l_m.list_of_particles = {};
  for (Bloque const & bloque : bloques) {
    l_m.list_of_particles.insert(l_m.list_of_particles.end(), bloque.lista_particulas.begin(),
                                 bloque.lista_particulas.end());
  }
  quickSort(l_m.list_of_particles, 0, l_m.list_of_particles.size() - 1);
  return l_m;
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
