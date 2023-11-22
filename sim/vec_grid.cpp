
#include "vec_grid.hpp"

//
// Created by sergio on 3/10/23.
//

void movimiento_particulas(Particula & particula, int index) {
  particula.pxyz[index][0] +=
      particula.hvxyz[index][0] * a_tiempo + particula.a_c[index][0] * std::pow(a_tiempo, 2);
  particula.pxyz[index][1] +=
      particula.hvxyz[index][1] * a_tiempo + particula.a_c[index][1] * std::pow(a_tiempo, 2);
  particula.pxyz[index][2] +=
      particula.hvxyz[index][2] * a_tiempo + particula.a_c[index][2] * std::pow(a_tiempo, 2);
  // se puede cambiar la división por * 0.5
  particula.vxyz[index][0]   = particula.hvxyz[index][0] + particula.a_c[index][0] * a_tiempo / 2;
  particula.vxyz[index][1]   = particula.hvxyz[index][1] + particula.a_c[index][1] * a_tiempo / 2;
  particula.vxyz[index][2]   = particula.hvxyz[index][2] + particula.a_c[index][2] * a_tiempo / 2;
  particula.hvxyz[index][0] += particula.a_c[index][0] * a_tiempo;
  particula.hvxyz[index][1] += particula.a_c[index][1] * a_tiempo;
  particula.hvxyz[index][2] += particula.a_c[index][2] * a_tiempo;
}

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
  bloques   = std::vector<Vec_Bloque>(borders[0] * borders[1] * borders[2], Vec_Bloque());
  size_cubo = borders[0] * borders[1] * borders[2];
  for (int j = 0; j < l_m.n_particulas; j++) {
    for (int i = 0; i < 3; i++) {
      l_m.particulas.bpos[j][i] =
          floor((l_m.particulas.pxyz[j][i] - min[i]) * borders[i] / (max[i] - min[i]));
      if (0 > l_m.particulas.bpos[j][i]) {
        l_m.particulas.bpos[j][i] = 0;
      } else if (l_m.particulas.bpos[j][i] > borders[i] - 1) {
        l_m.particulas.bpos[j][i] = borders[i] - 1;
      }
    }
    int const size =
        transform(l_m.particulas.bpos[j][0], l_m.particulas.bpos[j][1], l_m.particulas.bpos[j][2]);
    bloques[size].lista_particulas.push_back(j);
  }
  for (int i = 0; i < size_cubo; i++) { bloques[i].threeD_values(i, borders); }
  escribir_datos_iniciales();
}

void Grid::check_if_repos() {
  for (int i = 0; i < l_m.n_particulas; i++) {
    std::vector<double> newpos = {
      floor((l_m.particulas.pxyz[i][0] - min[0]) * borders[0] / (max[0] - min[0])),
      floor((l_m.particulas.pxyz[i][1] - min[1]) * borders[1] / (max[1] - min[1])),
      floor((l_m.particulas.pxyz[i][2] - min[2]) * borders[2] / (max[2] - min[2]))};
    for (int pos = 0; pos < 3; pos++) {
      if (0 > newpos[pos]) {
        newpos[pos] = 0;
      } else if (newpos[pos] > borders[pos] - 1) {
        newpos[pos] = borders[pos] - 1;
      }
    }
    if (l_m.particulas.bpos[i][0] != newpos[0] || l_m.particulas.bpos[i][1] != newpos[1] ||
        l_m.particulas.bpos[i][2] != newpos[2]) {
      reposicionar_particula(l_m.particulas, i, newpos);
    }
    l_m.particulas.densidad[i] = 0;
    l_m.particulas.a_c[i][0]   = 0;
    l_m.particulas.a_c[i][1]   = gravedad;
    l_m.particulas.a_c[i][2]   = 0;
  }
}

void Grid::reposicionar_particula(Particula & particula, int index, std::vector<double> newpos) {
  int pos = transform(particula.bpos[index][0], particula.bpos[index][1], particula.bpos[index][2]);
  for (size_t i = 0; i < bloques[pos].lista_particulas.size(); ++i) {
    if (bloques[pos].lista_particulas[i] == index) {
      bloques[pos].lista_particulas.erase(bloques[pos].lista_particulas.begin() + i);
      break;
    }
  }

  for (int i = 0; i < 3; ++i) { particula.bpos[index][i] = newpos[i]; }

  bloques[transform(particula.bpos[index][0], particula.bpos[index][1], particula.bpos[index][2])]
      .lista_particulas.push_back(index);
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
        if (x >= 0 && x < borders[0] && y >= 0 && y < borders[1] && z >= 0 && z < borders[2]) {
          adyacentes.push_back(bloques[transform(x, y, z)]);
        }
      }
    }
  }
  return adyacentes;
}

void Grid::incremento_densidad(double const h_2, double norma, int id1, int id2) {
  double const incremento       = (h_2 - norma) * (h_2 - norma) * (h_2 - norma);
  l_m.particulas.densidad[id1] += incremento;
  l_m.particulas.densidad[id2] += incremento;
}

void Grid::choques_entre_particulas() {
  for (int i = 0; i < size_cubo; ++i) {
    std::vector<Vec_Bloque> const adyacents = get_adyacents(i);
    for (Vec_Bloque const & bloque : adyacents) {
      for (int const & id1 : bloques[i].lista_particulas) {
        for (int const & id2 : bloque.lista_particulas) {
          if (id1 < id2) {
            double norma = 0;
            for (int j = 0; j < 3; j++) {
              norma += std::pow(l_m.particulas.pxyz[id2][j] - l_m.particulas.pxyz[id1][j], 2);
            }
            double const h_2 = std::pow(l_m.l_suavizado, 2);
            if (norma < h_2) { incremento_densidad(h_2, norma, id1, id2); }
          }
        }
      }
    }
  }
  for (int i = 0; i < l_m.n_particulas; i++) {
    l_m.particulas.densidad[i] =
        ((l_m.particulas.densidad[i] + std::pow(l_m.l_suavizado, m_num_6)) * 315 * l_m.masa_p) /
        (64 * std::numbers::pi * std::pow(l_m.l_suavizado, m_num_9));
  }
  transferencia_aceleracion();
}

void Grid::transferencia_aceleracion() {
  //auto t1 = clock();
  for (int i = 0; i < size_cubo; ++i) {
    std::vector<Vec_Bloque> const adyacents = get_adyacents(i);
    for (Vec_Bloque const & bloque : adyacents) {
      for (int const & id1 : bloques[i].lista_particulas) {
        for (int const & id2 : bloque.lista_particulas) {
          if (id1 < id2) {
            //auto t3 = clock();
            double norma = 0;
            for (int k = 0; k < 3; k++) {
              norma += std::pow(l_m.particulas.pxyz[id2][k] - l_m.particulas.pxyz[id1][k], 2);
            }
            if (norma < std::pow(l_m.l_suavizado, 2)) {

              incremento_aceleracion(l_m.particulas, id1, id2, norma);
            }
            //auto t4 = clock();
            //varac += double(t4-t3)/CLOCKS_PER_SEC;
          }
        }
      }
    }
  }
  //auto t2 = clock();
  //actransf += double(t2-t1)/CLOCKS_PER_SEC;
}

void Grid::incremento_aceleracion(Particula & particula, int index1, int index2,
                                  double norma) {

  double const dist                = std::pow(std::max(norma, std::pow(10, -12)), 0.5);
  double const operador_izquierda =
      (15 * l_m.masa_p * 1.5 * p_s * std::pow(l_m.l_suavizado - dist, 2) *
       (particula.densidad[index1] + particula.densidad[index2] - 2 * p_densidad)) /
      (std::numbers::pi * std::pow(l_m.l_suavizado, 6) * dist);
  for (int i = 0; i < 3; ++i) {
    particula.a_c[index1][i] +=
        ((particula.pxyz[index1][i] - particula.pxyz[index2][i]) * operador_izquierda +
         (particula.vxyz[index2][i] - particula.vxyz[index1][i]) * l_m.operador_derecha_ac) /
        (particula.densidad[index1] * particula.densidad[index2]);
    particula.a_c[index2][i] -=
        ((particula.pxyz[index1][i] - particula.pxyz[index2][i]) * operador_izquierda +
         (particula.vxyz[index2][i] - particula.vxyz[index1][i]) * l_m.operador_derecha_ac) /
        (particula.densidad[index1] * particula.densidad[index2]);
  }
}

void Grid::procesamiento_colisiones() {
  auto t1 = clock();
  for (Vec_Bloque & bloque : bloques) {
    if (bloque.b_x == 0 || bloque.b_x == borders[0] - 1) {
      bloque.colision_x(bloque.b_x, l_m.particulas);
    }
    if (bloque.b_y == 0 || bloque.b_y == borders[1] - 1) {
      bloque.colision_y(bloque.b_y, l_m.particulas);
    }
    if (bloque.b_z == 0 || bloque.b_z == borders[2] - 1) {
      bloque.colision_z(bloque.b_z, l_m.particulas);
    }

    for (int id : bloque.lista_particulas) { movimiento_particulas(l_m.particulas, id); }

    if (bloque.b_x == 0 || bloque.b_x == borders[0] - 1) {
      bloque.recinto_x(bloque.b_x, l_m.particulas);
    }
    if (bloque.b_y == 0 || bloque.b_y == borders[1] - 1) {
      bloque.recinto_y(bloque.b_y, l_m.particulas);
    }
    if (bloque.b_z == 0 || bloque.b_z == borders[2] - 1) {
      bloque.recinto_z(bloque.b_z, l_m.particulas);
    }
  }
  auto t2 = clock();
  colisiones += double(t2-t1)/CLOCKS_PER_SEC;
}

/*
void Grid::write_report(int n_iteaccion) {
  std::ofstream output("traza_iteraccion" + std::to_string(n_iteaccion) + ".txt");

  if (!output) { std::cerr << "No se pudo crear el archivo de texto." << '\n'; }
  for (int n = 0; n < size_cubo; n++) {
    output << "Bloque " << n << " - Número de partículas: " << bloques[n].lista_particulas.size()
           << '\n';
    for (int i: bloques[n].lista_particulas) {
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
}*/