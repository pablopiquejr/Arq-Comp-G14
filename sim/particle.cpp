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
  // Guardamos los nuevos datos en arrays convertidos a floats
  std::vector<float> data(pxyz.begin(),pxyz.end());

  std::vector<float> h_v(hvxyz.begin(),hvxyz.end());

  std::vector<float> v_aux(vxyz.begin(),vxyz.end());

  data.insert(data.end(), h_v.begin(),h_v.end());
  data.insert(data.end(), v_aux.begin(),v_aux.end());
  return data;
}

void Particula::printinfo() const {
  std::cout << "Particula" << identifier << '\n';
  std::cout << "px:  " << pxyz[0] << '\t';
  std::cout << "py:  " << pxyz[1] << '\t';
  std::cout << "pz:  " << pxyz[2] << '\t';
  std::cout << "hvx:  " << hvxyz[0] << '\t';
  std::cout << "hvy " << hvxyz[1] << '\t';
  std::cout << "hvz " << hvxyz[2] << '\t';
  std::cout << "vx:  " << vxyz[0] << '\t';
  std::cout << "vy " << vxyz[1] << '\t';
  std::cout << "vz " << vxyz[2] << '\n';
}

void Particula::set_particles_data(std::ifstream & file, double id) {
  identifier = id;
  pxyz[0]         = read_float(file);
  pxyz[1]         = read_float(file);
  pxyz[2]         = read_float(file);
  hvxyz[0]        = read_float(file);
  hvxyz[1]        = read_float(file);
  hvxyz[2]        = read_float(file);
  vxyz[0]         = read_float(file);
  vxyz[1]         = read_float(file);
  vxyz[2]         = read_float(file);
}

// ESTAS DOS FUNCIONES ERAN DE BLOQUE
//  SI USAS DATOS DE PARTICULA PIENSA SI RENTA MAS TENER ESTA FUNCIÓN DENTRO DE LA CLASE
void Particula::transformacion_densidad(double h_logitud_suavizado, double masa_p) {
  // SI aqui usas PI, creo que hay una libreria para eso, deberias usarla
  densidad = ((densidad + std::pow(h_logitud_suavizado, m_num_6)) * 315 * masa_p) /
             (64 * std::numbers::pi * std::pow(h_logitud_suavizado, m_num_9));
}

void Particula::movimiento_particulas() {
  pxyz[0] += hvxyz[0] * a_tiempo + a_c[0] * pow(a_tiempo, 2);
  pxyz[1] += hvxyz[1] * a_tiempo + a_c[1] * pow(a_tiempo, 2);
  pxyz[2] += hvxyz[2] * a_tiempo + a_c[2] * pow(a_tiempo, 2);
  // se puede cambiar la división por * 0.5
  vxyz[0]   = hvxyz[0] + a_c[0] * a_tiempo / 2;
  vxyz[1]   = hvxyz[1] + a_c[1] * a_tiempo / 2;
  vxyz[2]   = hvxyz[2] + a_c[2] * a_tiempo / 2;
  hvxyz[0] += a_c[0] * a_tiempo;
  hvxyz[1] += a_c[1] * a_tiempo;
  hvxyz[2] += a_c[2] * a_tiempo;
  repos= false;
}
