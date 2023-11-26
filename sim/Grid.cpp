
#include "Grid.hpp"

//
// Created by sergio on 3/10/23.
//

void movimiento_particulas(Particula & particula, int index) {
  for (int i = 0; i < 3; i++){
    particula.pxyz[index][i] +=
        particula.hvxyz[index][i] * a_tiempo + particula.a_c[index][i] * std::pow(a_tiempo, 2);
    particula.vxyz[index][i]   = particula.hvxyz[index][i] + particula.a_c[index][i] * a_tiempo * m_half;
    particula.hvxyz[index][i] += particula.a_c[index][i] * a_tiempo;

  }
  /*
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

   */
}

void Grid::escribir_datos_iniciales() {
  std::cout << "Number of particles: " << l_m.n_particulas << '\n'
            << "Particles per meter: " << l_m.ppm << "\n"
            << "Smoothing Length: " << l_m.l_suavizado << '\n'
            << "Particles mass: " << l_m.masa_p << '\n'
            << "Grid size: " << borders[0] << " * " << borders[1] << " * " << borders[2] << '\n'
            << "Number of blocks: " << size_cubo << '\n'
            << "Bloque size: " << (max[0] - min[0]) / borders[0] << " * "
            << (max[1] - min[1]) / borders[1] << " * " << (max[2] - min[2]) / borders[2] << '\n';
}

/*
 FORMAS QUE SE PROBARON ANTES DE DESCUBRIR EL .AT PARA ITERAR ARRAYS
for (int i = 0; i < 3; i++) { borders[i] = floor((max[i] - min[i]) / l_m.l_suavizado); }

auto it_borders    = borders.begin();
auto it_min        = min.begin();
auto it_max        = max.begin();
while (it_min != min.end() && it_max != max.end() && it_borders != borders.end()) {
  *it_borders = static_cast<int>(std::floor((*it_max - *it_min) / l_m.l_suavizado));
  ++it_min;
  ++it_max;
  ++it_borders;
}

for (const auto [minValue, maxValue] : std::ranges::views::(min, max)) {
  borders[&borders - &minValue] = static_cast<int>(std::floor((maxValue - minValue) /
l_m.l_suavizado));
}
borders[0] = floor((max[0] - min[0]) / l_m.l_suavizado);
borders[1] = floor((max[1] - min[1]) / l_m.l_suavizado);
borders[2] = floor((max[2] - min[2]) / l_m.l_suavizado);
*/

void Grid::primeros_calculos() {
  for (int i = 0; i < 3; i++) { borders.at(i) = floor((max.at(i) - min.at(i)) / l_m.l_suavizado); }
  size_cubo = borders.at(0) * borders.at(1) * borders.at(2);
  bloques   = std::vector<Vec_Bloque>(size_cubo, Vec_Bloque());
  for (int j = 0; j < l_m.n_particulas; j++) {
    for (int i = 0; i < 3; i++) {
      l_m.particulas.bpos.at(j).at(i) = floor((l_m.particulas.pxyz.at(j).at(i) - min.at(i)) *
                                              borders.at(i) / (max.at(i) - min.at(i)));
      if (0 > l_m.particulas.bpos.at(j).at(i)) {
        l_m.particulas.bpos.at(j).at(i) = 0;
      } else if (l_m.particulas.bpos.at(j).at(i) > borders.at(i) - 1) {
        l_m.particulas.bpos.at(j).at(i) = borders.at(i) - 1;
      }
    }
    int const size = transform(l_m.particulas.bpos.at(j).at(0), l_m.particulas.bpos.at(j).at(1),
                               l_m.particulas.bpos.at(j).at(2));
    bloques.at(size).lista_particulas.push_back(j);
  }
  for (int i = 0; i < size_cubo; i++) { bloques.at(i).threeD_values(i, borders); }
  escribir_datos_iniciales();
}

void Grid::check_if_repos() {
  for (int i = 0; i < l_m.n_particulas; i++) {
    std::array<int, 3> newpos = {static_cast<int>(floor((l_m.particulas.pxyz[i][0] - min[0]) *
                                                        borders[0] / (max[0] - min[0]))),
                                 static_cast<int>(floor((l_m.particulas.pxyz[i][1] - min[1]) *
                                                        borders[1] / (max[1] - min[1]))),
                                 static_cast<int>(floor((l_m.particulas.pxyz[i][2] - min[2]) *
                                                        borders[2] / (max[2] - min[2])))};
    // Solucion de ChatGPT para evitar iterar arrays de tamaño 3 en un bucle for
    std::transform(std::begin(newpos), std::end(newpos), std::begin(borders), std::begin(newpos),
                   [](int pos, int border) {
                     return std::clamp(pos, 0, border - 1);
                   });
    if (l_m.particulas.bpos[i][0] != newpos[0] || l_m.particulas.bpos[i][1] != newpos[1] ||
        l_m.particulas.bpos[i][2] != newpos[2]) {
      reposicionar_particula(l_m.particulas, i, newpos);
    }
    l_m.particulas.densidad[i] = 0;
    l_m.particulas.a_c[i]      = {0, gravedad, 0};
  }
}

void Grid::reposicionar_particula(Particula & particula, int index, std::array<int, 3> newpos) {
  int const pos =
      transform(particula.bpos[index][0], particula.bpos[index][1], particula.bpos[index][2]);
  for (auto it = bloques[pos].lista_particulas.begin(); it != bloques[pos].lista_particulas.end();
       ++it) {
    if (*it == index) {
      bloques[pos].lista_particulas.erase(it);
      break;
    }
  }
  for (int i = 0; i < 3; ++i) { particula.bpos[index].at(i) = newpos.at(i); }

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
        int const n_bx = bloques[i].b_x + dx;
        int const n_by = bloques[i].b_y + dy;
        int const n_bz = bloques[i].b_z + dz;
        if (n_bx >= 0 && n_bx < borders[0] && n_by >= 0 && n_by < borders[1] && n_bz >= 0 &&
            n_bz < borders[2]) {
          adyacentes.push_back(bloques[transform(n_bx, n_by, n_bz)]);
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
        ((l_m.particulas.densidad[i] + std::pow(l_m.l_suavizado, m_num_6)) * m_num_315 *
         l_m.masa_p) /
        (m_num_64 * std::numbers::pi * std::pow(l_m.l_suavizado, m_num_9));
  }
  transferencia_aceleracion();
}

void Grid::transferencia_aceleracion() {
  for (int i = 0; i < size_cubo; ++i) {
    std::vector<Vec_Bloque> const adyacents = get_adyacents(i);
    for (Vec_Bloque const & bloque : adyacents) {
      for (int const & id1 : bloques[i].lista_particulas) {
        for (int const & id2 : bloque.lista_particulas) {
          if (id1 < id2) {
            double norma = 0;
            for (int k = 0; k < 3; k++) {
              norma += std::pow(l_m.particulas.pxyz[id2][k] - l_m.particulas.pxyz[id1][k], 2);
            }
            if (norma < std::pow(l_m.l_suavizado, 2)) {
              incremento_aceleracion(l_m.particulas, id1, id2, norma);
            }
          }
        }
      }
    }
  }
}

void Grid::incremento_aceleracion(Particula & particula, int index1, int index2,
                                  double norma) const {
  double const dist = std::pow(std::max(norma, std::pow(10, -12)), 0.5);
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

    for (int const i_d : bloque.lista_particulas) { movimiento_particulas(l_m.particulas, i_d); }

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