
#include "vec_grid.hpp"

//
// Created by sergio on 3/10/23.
//

void Grid::escribir_datos_iniciales() {
  std::cout << "Numero de Partículas: " << l_m.n_particulas << '\n'
            << "Particles Per Meter: " << l_m.ppm << "\n"
            << "Longitud de suavizado: " << l_m.l_suavizado << '\n'
            << "Masa de particula: " << l_m.masa_p << '\n'
            << "Tamaño Bloque: " << borders[0] << " * " << borders[1] << " * " << borders[2] << '\n'
            << "Numero de Bloques: " << size_cubo << '\n'
            << "Tamaño Bloque: " << borders[0] / max[0] << " * " << borders[1] / max[0] << " * "
            << borders[2] / max[2] << '\n';
}

void Grid::primeros_calculos() {
  for (int i = 0; i < 3; i++) { borders[i] = floor((max[i] - min[i]) / l_m.l_suavizado); }
  size_cubo = borders[0] * borders[1] * borders[2];
  bloques   = std::vector<Vec_Bloque>(size_cubo, Vec_Bloque());
  for (Particula & particula : l_m.list_of_particles) {
    for (int i = 0; i < 3; i++) {
      particula.bpos[i] = floor((particula.pxyz[i] - min[i]) * borders[i] / (max[i] - min[i]));
      if (0 > particula.bpos[i]) {
        particula.bpos[i] = 0;
      } else if (particula.bpos[i] > borders[i] - 1) {
        particula.bpos[i] = borders[i] - 1;
      }
    }
    int const size = transform(particula.bpos[0], particula.bpos[1], particula.bpos[2]);
    bloques[size].lista_particulas.push_back(particula.identifier);
  }
  for (int i = 0; i < size_cubo; i++) { bloques[i].threeD_values(i, borders); }
  escribir_datos_iniciales();
}

void Grid::check_if_repos() {
  for (Particula & particula : l_m.list_of_particles) {
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
      reposicionar_particula(particula, newpos);
    }
    particula.densidad = 0;
    particula.a_c[0]   = 0;
    particula.a_c[1]   = gravedad;
    particula.a_c[2]   = 0;
  }
}

void Grid::reposicionar_particula(Particula & particula, std::vector<double> newpos) {
  int pos = transform(particula.bpos[0], particula.bpos[1], particula.bpos[2]);
  for (size_t i = 0; i < bloques[pos].lista_particulas.size(); ++i) {
    if (bloques[pos].lista_particulas[i] == particula.identifier) {
      bloques[pos].lista_particulas.erase(bloques[pos].lista_particulas.begin() + i);
      break;
    }
  }

  for (int i = 0; i < 3; ++i) { particula.bpos[i] = newpos[i]; }

  bloques[transform(particula.bpos[0], particula.bpos[1], particula.bpos[2])]
      .lista_particulas.push_back(particula.identifier);
}

int Grid::transform(int i, int j, int k) {
  int const size = i + j * borders[0] + k * borders[0] * borders[1];
  return size;
}

std::vector<Vec_Bloque> Grid::get_adyacents(int i) {
  std::vector<Vec_Bloque> adyacentes;
  for (int dx = -1; dx <= 1; dx++) {
    for (int dy = -1; dy <= 1; dy++) {
      for (int dz = -1; dz <= 1; dz++) {
        int const x = bloques[i].b_x + dx;
        int const y = bloques[i].b_y + dy;
        int const z = bloques[i].b_z + dz;
        if (!(x < 0 || x >= borders[0] || y < 0 || y >= borders[1] || z < 0 || z >= borders[2])) {
          adyacentes.push_back(bloques[transform(x, y, z)]);
        }
      }
    }
  }
  return adyacentes;
}

void Grid::incremento_densidades(int & id1, int & id2) {
  double const norma =
      std::pow(l_m.list_of_particles[id2].pxyz[0] - l_m.list_of_particles[id1].pxyz[0], 2) +
      std::pow(l_m.list_of_particles[id2].pxyz[1] - l_m.list_of_particles[id1].pxyz[1], 2) +
      std::pow(l_m.list_of_particles[id2].pxyz[2] - l_m.list_of_particles[id1].pxyz[2], 2);
  double const h_2 = std::pow(l_m.l_suavizado, 2);
  if (norma < h_2) {
    double const incremento              = std::pow(h_2 - norma, 3);
    l_m.list_of_particles[id1].densidad += incremento;
    l_m.list_of_particles[id2].densidad += incremento;
  }
}

void Grid::choques_entre_particulas() {
  /////////PUEDE QUE CON INT NOS PASEMOS DE RANGO
  for (int i = 0; i < size_cubo; ++i) {
    std::vector<Vec_Bloque> adyacents = get_adyacents(i);
    for (Vec_Bloque & bloque : adyacents) {
      for (int & id1 : bloques[i].lista_particulas) {
        for (int & id2 : bloque.lista_particulas) {
          if (id1 < id2) { incremento_densidades(id1, id2); }
        }
      }
    }
  }
  for (Particula & particula : l_m.list_of_particles) {
    particula.transformacion_densidad(l_m.l_suavizado, l_m.masa_p);
  }
  transferencia_aceleracion();
}

void Grid::transferencia_aceleracion() {
  for (int i = 0; i < size_cubo; ++i) {
    std::vector<Vec_Bloque> adyacents = get_adyacents(i);
    for (Vec_Bloque & bloque : adyacents) {
      for (int & id1 : bloques[i].lista_particulas) {
        for (int & id2 : bloque.lista_particulas) {
          if (id1 < id2) {
            double const norma =
                std::pow(l_m.list_of_particles[id2].pxyz[0] - l_m.list_of_particles[id1].pxyz[0],
                         2) +
                std::pow(l_m.list_of_particles[id2].pxyz[1] - l_m.list_of_particles[id1].pxyz[1],
                         2) +
                std::pow(l_m.list_of_particles[id2].pxyz[2] - l_m.list_of_particles[id1].pxyz[2],
                         2);
            if (norma < std::pow(l_m.l_suavizado, 2)) {
              incremento_aceleracion(l_m.list_of_particles[id1], l_m.list_of_particles[id2], norma);
            }
          }
        }
      }
    }
  }
}

void Grid::incremento_aceleracion(Particula & particula_i, Particula & particula_j,
                                  double norma) const {
  std::vector<double> var_ac = {0, 0, 0, 0, 0, 0};
  double dist                = std::pow(std::max(norma, std::pow(10, -12)), 0.5);
  double const operador_izquierda =
      (15 * l_m.masa_p * 1.5 * p_s * std::pow(l_m.l_suavizado - dist, 2) *
       (particula_i.densidad + particula_j.densidad - 2 * p_densidad)) /
      (std::numbers::pi * std::pow(l_m.l_suavizado, 6) * dist);
  double const operador_derecha =
      45 * u_viscosidad * l_m.masa_p / (std::numbers::pi * std::pow(l_m.l_suavizado, 6));
  for (int i = 0; i < 3; ++i) {
    var_ac[i]     = (particula_i.pxyz[i] - particula_j.pxyz[i]) * operador_izquierda;
    var_ac[i + 3] = (particula_j.vxyz[i] - particula_i.vxyz[i]) * operador_derecha;
  }
  for (size_t i = 0; i < 3; i++) {
    particula_i.a_c[i] +=
        (var_ac[i] + var_ac[i + 3]) / (particula_i.densidad * particula_j.densidad);
    particula_j.a_c[i] -=
        (var_ac[i] + var_ac[i + 3]) / (particula_i.densidad * particula_j.densidad);
  }
}

void Grid::procesamiento_colisiones() {
  for (Vec_Bloque & bloque : bloques) {
    if (bloque.b_x == 0 || bloque.b_x == borders[0] - 1) {
      bloque.colision_x(bloque.b_x, l_m.list_of_particles);
    }
    if (bloque.b_y == 0 || bloque.b_y == borders[1] - 1) {
      bloque.colision_y(bloque.b_y, l_m.list_of_particles);
    }
    if (bloque.b_z == 0 || bloque.b_z == borders[2] - 1) {
      bloque.colision_z(bloque.b_z, l_m.list_of_particles);
    }

    for (int id : bloque.lista_particulas) { l_m.list_of_particles[id].movimiento_particulas(); }

    if (bloque.b_x == 0 || bloque.b_x == borders[0] - 1) {
      bloque.recinto_x(bloque.b_x, l_m.list_of_particles);
    }
    if (bloque.b_y == 0 || bloque.b_y == borders[1] - 1) {
      bloque.recinto_y(bloque.b_y, l_m.list_of_particles);
    }
    if (bloque.b_z == 0 || bloque.b_z == borders[2] - 1) {
      bloque.recinto_z(bloque.b_z, l_m.list_of_particles);
    }
  }
}

void Grid::colision_limites() {
  for (Vec_Bloque & bloque : bloques) {
    if (bloque.b_z == 0) {
      bloque.colision_z_baja(l_m.list_of_particles);
    } if (bloque.b_z == borders[2] - 1) {
      bloque.colision_z_alta(l_m.list_of_particles);
    } if (bloque.b_y == 0) {
      bloque.colision_y_baja(l_m.list_of_particles);
    } if (bloque.b_y == borders[1] - 1) {
      bloque.colision_y_alta(l_m.list_of_particles);
    } if (bloque.b_x == 0) {
      bloque.colision_x_baja(l_m.list_of_particles);
    } if (bloque.b_x == borders[0] - 1) {
      bloque.colision_x_alta(l_m.list_of_particles);
    } else {
      for (int i_d : bloque.lista_particulas) { l_m.list_of_particles[i_d].movimiento_particulas(); }
    }
  }
}



void Grid::write_report(int n_iteaccion) {
  std::ofstream output("traza_large_iteraccion" + std::to_string(n_iteaccion) + ".txt");

  if (!output) { std::cerr << "No se pudo crear el archivo de texto." << '\n'; }
  for (int n = 0; n < size_cubo; n++) {
    output << "Bloque " << n << " - Número de partículas: " << bloques[n].lista_particulas.size()
           << '\n';
    for (int i : bloques[n].lista_particulas) {
      Particula particles = l_m.list_of_particles[i];
      output << "Particula " << particles.identifier << '\n';
      output << "Posición (x, y, z): " << particles.pxyz[0] << ", " << particles.pxyz[1] << ", "
             << particles.pxyz[2] << '\n';
      output << "HV (x, y, z): " << particles.hvxyz[0] << ", " << particles.hvxyz[1] << ", "
             << particles.hvxyz[2] << '\n';
      output << "Velocidad (x, y, z): " << particles.vxyz[0] << ", " << particles.vxyz[1] << ", "
             << particles.vxyz[2] << '\n';
      output << "Densidad: " << particles.densidad << '\n';
      output << "Aceleración (x, y, z): " << particles.a_c[0] << ", " << particles.a_c[1] << ", "
             << particles.a_c[2] << '\n';
      output << '\n';
    }
  }
}

/* VERSION ANTIGUA
 vertices =
std::vector<int>{0,
                borders[0] - 1,
                (borders[1] - 1) * borders[0],
                borders[0] - 1 + (borders[1] - 1) * borders[0],
                (borders[2] - 1) * borders[0] * borders[1],
                borders[0] - 1 + (borders[2] - 1) * borders[0] * borders[1],
                (borders[1] - 1) * borders[0] + (borders[2] - 1) * borders[0] * borders[1],
                size_cubo};


void Grid::choques_entre_particulas() {
  /////////PUEDE QUE CON INT NOS PASEMOS DE RANGO
  for (int i = 0; i < size_cubo; ++i) {
    // Comprobar si es un vertice -> cada vertice colisiona con 7 bloques (excluyendose)
    if (i == 0 || i == borders[0] - 1 || i == (borders[1] - 1) * borders[0] ||
        i == (borders[0] - 1 + (borders[1] - 1) * borders[0]) ||
        i == (borders[2] - 1) * borders[0] * borders[1] ||
        i == borders[0] - 1 + (borders[2] - 1) * borders[0] * borders[1] ||
        i == ((borders[1] - 1) * borders[0] + (borders[2] - 1) * borders[0] * borders[1]) ||
        i == size_cubo) {
      for (int pos : vertices) {
        if (pos != i) { comprobar_reposicionamiento(bloques[i], bloques[pos]); }
      }
    }
    // cada bloque de una arista colisiona con 11 bloques
    else if (es_arista(i)) {
      // x
      colisiones abajo = [ i - 1, i + 1 ];
      arriba = [ i + 15, i + 16, i + 17 ] enfrente = [ i + 315, i + 316, i + 317 ] arr_enfrente =
          [ i + 330, i + 331, i + 332 ]

          colisiones abajo = [ i - 15, i + 15 ];
      arriba               = [ i - 1, i + 1 ];
      enfrente = [ i + 315, i + 316, i + 317 ] arr_enfrente = [ i + 330, i + 331, i + 332 ]

    }

    else if (es_pared(i)) {
    }
  }

  for (Particula & particula : l_m.list_of_particles) {
    particula.transformacion_densidad(l_m.l_suavizado, l_m.masa_p);
  }
}
}

 */

/*
void Grid::adyacent_subx(std::vector<int> const & coor, std::vector<Vec_Bloque> & adyacentes) {
  try {
    adyacentes.push_back(bloques[transform(coor[0] - 1, coor[1] - 1, coor[2] - 1)]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0] - 1, coor[1] - 1, coor[2])]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0] - 1, coor[1] - 1, coor[2] + 1)]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0] - 1, coor[1], coor[2] - 1)]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0] - 1, coor[1], coor[2])]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0] - 1, coor[1], coor[2] + 1)]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0] - 1, coor[1] + 1, coor[2] - 1)]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0] - 1, coor[1] + 1, coor[2])]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0] - 1, coor[1] + 1, coor[2] + 1)]);
  } catch (...) { };
}

void Grid::adyacent_x(std::vector<int> const & coor, std::vector<Vec_Bloque> & adyacentes) {
  try {
    adyacentes.push_back(bloques[transform(coor[0], coor[1] - 1, coor[2] - 1)]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0], coor[1] - 1, coor[2])]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0], coor[1] - 1, coor[2] + 1)]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0], coor[1], coor[2] - 1)]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0], coor[1], coor[2])]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0], coor[1], coor[2] + 1)]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0], coor[1] + 1, coor[2] - 1)]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0], coor[1] + 1, coor[2])]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0], coor[1] + 1, coor[2] + 1)]);
  } catch (...) { };
}

void Grid::adyacent_plusx(std::vector<int> const & coor, std::vector<Vec_Bloque> & adyacentes) {
  try {
    adyacentes.push_back(bloques[transform(coor[0] + 1, coor[1] - 1, coor[2] - 1)]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0] + 1, coor[1] - 1, coor[2])]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0] + 1, coor[1] - 1, coor[2] + 1)]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0] + 1, coor[1], coor[2] - 1)]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0] + 1, coor[1], coor[2])]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0] + 1, coor[1], coor[2] + 1)]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0] + 1, coor[1] + 1, coor[2] - 1)]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0] + 1, coor[1] + 1, coor[2])]);
  } catch (...) { };
  try {
    adyacentes.push_back(bloques[transform(coor[0] + 1, coor[1] + 1, coor[2] + 1)]);
  } catch (...) { };
}

std::vector<Vec_Bloque> Grid::get_adyacents(int i) {
  std::vector<int> const coor = {(i % (borders[0] * borders[1])) % borders[0],
                                 (i % (borders[0] * borders[1])) / borders[0],
                                 i / (borders[0] * borders[1])};
  std::vector<Vec_Bloque> adyacentes;

  adyacent_subx(coor, adyacentes);
  adyacent_x(coor, adyacentes);
  adyacent_plusx(coor, adyacentes);

  return adyacentes;
}
*/
