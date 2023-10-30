//
// Created by sergio on 3/10/23.
//
#include "grid.hpp"

// SE PASA DE COMPLEJIDAD

/* VERSION PREVIA DE ESTA FUNCIÓN
 * void incremento_aceleracion(Particula & particula_i, Particula & particula_j, double norma) {
// izquierda x,y,z derecha x,y,z
std::vector<double> incremento_aceleracion = {0,0,0,0,0,0};
// vector resultado x,y,z
std::vector<double> incremento_total = {0,0,0};
double const operador_izquierda =
    // el 1.5 es 3/2
    15 * masa_p * 1.5 * p_s * std::pow(h_logitud_suavizado - std::pow(std::max(norma,
std::pow(10, -12)), 0.5), 2) * (particula_i.densidad + particula_j.densidad - 2 * (std::pow(10,
-3))) / (std::numbers::pi  * std::pow(h_logitud_suavizado, 6) * std::pow(std::max(norma,
std::pow(10, -12)), 0.5)); double const operador_derecha = 45 * 0.4 * masa_p /
(std::numbers::pi  * std::pow(h_logitud_suavizado, 6));

 double const incremento_aceleracion_iz_x = (particula_i.px - particula_j.px) * operador_izquierda;
 double const incremento_aceleracion_iz_y = (particula_i.py - particula_j.py) * operador_izquierda;
 double const incremento_aceleracion_iz_z = (particula_i.pz - particula_j.pz) * operador_izquierda;
 double const incremento_aceleracion_der_x = (particula_j.vx - particula_i.vx) * operador_derecha;
 double const incremento_aceleracion_der_y = (particula_j.vy - particula_i.vy) * operador_derecha;
 double const incremento_aceleracion_der_z = (particula_j.vz - particula_i.vz) * operador_derecha;
 double const incremento_aceleracion_x =
     (incremento_aceleracion_iz_x + incremento_aceleracion_der_x) /
     (particula_i.densidad * particula_j.densidad);
 double const incremento_aceleracion_y =
     (incremento_aceleracion_iz_y + incremento_aceleracion_der_y) /
     (particula_i.densidad * particula_j.densidad);
 double const incremento_aceleracion_z =
     (incremento_aceleracion_iz_z + incremento_aceleracion_der_z) /
     (particula_i.densidad * particula_j.densidad);

particula_i.acx  += incremento_aceleracion_x;
particula_j.acx  += incremento_aceleracion_x;
particula_i.acy += incremento_aceleracion_y;
particula_j.acy += incremento_aceleracion_y;
particula_i.acz += incremento_aceleracion_z;
particula_j.acz += incremento_aceleracion_z;
 }
*/

// variación de acelaración (incremento)-> izquierda x,y,z (p)  derecha x,y,z (v) resultado x,y,z

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
  var_ac[0]       = (particula_i.px - particula_j.px) * operador_izquierda;
  var_ac[1]       = (particula_i.py - particula_j.py) * operador_izquierda;
  var_ac[2]       = (particula_i.pz - particula_j.pz) * operador_izquierda;
  var_ac[3]       = (particula_j.vx - particula_i.vx) * operador_derecha;
  var_ac[4]       = (particula_j.vy - particula_i.vy) * operador_derecha;
  var_ac[m_num_5] = (particula_j.vz - particula_i.vz) * operador_derecha;
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
  double const norma = std::pow(particula_i.px - particula_j.px, 2) +
                       std::pow(particula_i.py - particula_j.py, 2) +
                       std::pow(particula_i.pz - particula_j.pz, 2);
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
  n_x = floor((x_max - x_min) / l_m.l_suavizado);
  n_y = floor((y_max - y_min) / l_m.l_suavizado);
  n_z = floor((z_max - z_min) / l_m.l_suavizado);
}

void Cubo::creacion_bloques() {
  for (int i = 0; i < n_x; i++) {
    for (int j = 0; j < n_y; j++) {
      for (int k = 0; k < n_z; k++) {
        Bloque const bloque(i, j, k);
        bloques.push_back(bloque);
      }
    }
  }
  asignacion_inicial();
}

void Cubo::asignacion_inicial() {
  for (Particula particula : l_m.list_of_particles) {
    set_particles_coordinates(particula);
    for (Bloque bloque : bloques) {
      if (particula.i == bloque.b_x && particula.j == bloque.b_y && particula.k == bloque.b_z) {
        bloque.lista_particulas.push_back(particula);
      }
    }
  }
}

void Cubo::choques_entre_particulas() {
  // Esto tiene en cuenta consigo mismo tmb eso esta bien?
  for (Bloque const & bloque : bloques) {
    for (Bloque const & bloque2 : bloques) {
      if (bloque.b_x == bloque2.b_x - 1 || bloque.b_x == bloque2.b_x ||
          bloque.b_x == bloque2.b_x + 1 || bloque.b_y == bloque2.b_y - 1 ||
          bloque.b_y == bloque2.b_y || bloque.b_y == bloque2.b_y + 1 ||
          bloque.b_z == bloque2.b_z - 1 || bloque.b_z == bloque2.b_z ||
          bloque.b_z == bloque2.b_z + 1) {
        for (Particula particula : bloque.lista_particulas) {
          for (Particula particula2 : bloque2.lista_particulas) {
            if (particula.identifier < particula2.identifier) {
              incremento_densidades(particula, particula2, l_m);
            }
          }
        }
      }
    }
  }
}

void Cubo::set_particles_coordinates(Particula & particula) const {
  particula.i = floor((particula.px - x_min) * n_x / (x_max - x_min));
  if (0 > particula.i) {
    particula.i = 0;
  } else if (particula.i > n_x - 1) {
    particula.i = n_x - 1;
  }
  particula.j = floor((particula.py - y_min) * n_y / (y_max - y_min));
  if (0 > particula.j) {
    particula.j = 0;
  } else if (particula.j > n_y - 1) {
    particula.j = n_y - 1;
  }
  particula.k = floor((particula.pz - z_min) * n_z / (z_max - z_min));
  if (0 > particula.k) {
    particula.k = 0;
  } else if (particula.k > n_z - 1) {
    particula.k = n_z - 1;
  }
}

// IDEA: meter el movimiento dentro de colision_baja
void Cubo::colision_limites() {
  for (Bloque & bloque : bloques) {
    if (bloque.b_x == 0) { bloque.colision_x_baja(); }
    if (bloque.b_x == n_x - 1) { bloque.colision_x_alta(); }
    if (bloque.b_y == 0) { bloque.colision_y_baja(); }
    if (bloque.b_y == n_y - 1) { bloque.colision_y_alta(); }
    if (bloque.b_z == 0) { bloque.colision_z_baja(); }
    if (bloque.b_z == n_z - 1) { bloque.colision_z_alta(); }
    for (Particula & particula : bloque.lista_particulas) {
      particula.movimiento_particulas();
    }  // mover_particulas_bloque(); //no implementada (leer fijado discord)
  }
}
