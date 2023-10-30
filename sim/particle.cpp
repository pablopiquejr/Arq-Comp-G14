//
// Created by sergio on 5/10/23.
//
#include "particle.hpp"

double read_float(std::ifstream & file) {
  float number = 0;
  // NOLINTNEXTLINE
  file.read(reinterpret_cast<char *>(&number), 4);
  return number;
}

std::vector<float> Particula::particle_write() const {
  auto n_px                     = (float) px;
  auto n_py                     = (float) py;
  auto n_pz                     = (float) pz;
  auto n_hvx                    = (float) hvx;
  auto n_hvy                    = (float) hvy;
  auto n_hvz                    = (float) hvz;
  auto n_vx                     = (float) vx;
  auto n_vy                     = (float) vy;
  auto n_vz                     = (float) vz;
  std::vector<float> const data = {n_px, n_py, n_pz, n_hvx, n_hvy, n_hvz, n_vx, n_vy, n_vz};
  return data;
}

void Particula::printinfo(int counter) const {
  std::cout << "Particula" << counter << '\n';
  std::cout << "px:  " << px << '\t';
  std::cout << "py:  " << py << '\t';
  std::cout << "pz:  " << pz << '\t';
  std::cout << "hvx:  " << hvx << '\t';
  std::cout << "hvy " << hvy << '\t';
  std::cout << "hvz " << hvz << '\t';
  std::cout << "vx:  " << vx << '\t';
  std::cout << "vy " << vy << '\t';
  std::cout << "vz " << vz << '\n';
}

void Particula::set_particles_data(std::ifstream & file, double id) {
  identifier = id;
  px         = read_float(file);
  py         = read_float(file);
  pz         = read_float(file);
  hvx        = read_float(file);
  hvy        = read_float(file);
  hvz        = read_float(file);
  vx         = read_float(file);
  vy         = read_float(file);
  vz         = read_float(file);
}

// ESTAS DOS FUNCIONES ERAN DE BLOQUE
//  SI USAS DATOS DE PARTICULA PIENSA SI RENTA MAS TENER ESTA FUNCIÓN DENTRO DE LA CLASE
void Particula::transformacion_densidad(double h_logitud_suavizado, double masa_p) {
  // SI aqui usas PI, creo que hay una libreria para eso, deberias usarla
  densidad = (densidad + std::pow(h_logitud_suavizado, m_num_6)) * 315 * masa_p /
             (64 * std::numbers::pi * std::pow(h_logitud_suavizado, m_num_9));
}

void Particula::movimiento_particulas() {
  px += hvx * a_tiempo + a_c[0] * pow(a_tiempo, 2);
  py += hvy * a_tiempo + a_c[1] * pow(a_tiempo, 2);
  pz += hvz * a_tiempo + a_c[2] * pow(a_tiempo, 2);
  // se puede cambiar la división por * 0.5
  vx   = hvx + a_c[0] * a_tiempo / 2;
  vy   = hvy + a_c[1] * a_tiempo / 2;
  vz   = hvz + a_c[2] * a_tiempo / 2;
  hvx += a_c[0] * a_tiempo;
  hvy += a_c[1] * a_tiempo;
  hvz += a_c[2] * a_tiempo;
}
