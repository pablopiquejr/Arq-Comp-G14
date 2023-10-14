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

std::string Particula::particle_write() const {
  std::string parameters;
  parameters += std::to_string(px);
  parameters += std::to_string(py);
  parameters += std::to_string(pz);
  parameters += std::to_string(hvx);
  parameters += std::to_string(hvy);
  parameters += std::to_string(hvz);
  parameters += std::to_string(vx);
  parameters += std::to_string(vy);
  parameters += std::to_string(vz);
  return parameters;
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
  px  = read_float(file);
  py  = read_float(file);
  pz  = read_float(file);
  hvx = read_float(file);
  hvy = read_float(file);
  hvz = read_float(file);
  vx  = read_float(file);
  vy  = read_float(file);
  vz  = read_float(file);
}

