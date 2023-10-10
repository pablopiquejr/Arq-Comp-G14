//
// Created by sergio on 5/10/23.
//

#include "particle.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

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

void Particula::set_particles_coordinates(std::ifstream & file) {
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

double calculo_m(double ppm, double p) {
  double const ppm_cubo = std::pow(ppm, 3.0);
  double const masa     = p / ppm_cubo;
  return masa;
}

double calculo_h(double ppm, double r) {
  double const height = r / ppm;
  return height;
}

double calculo_nx(double xmax, double xmin, double h) {
  double const n_x = (xmax - xmin) / h;
  return n_x;
}

double calculo_ny(double h, double ymax, double ymin) {
  double const n_y = (ymax - ymin) / h;
  return n_y;
}

double calculo_nz(double h, double zmax, double zmin) {
  double const n_z = (zmax - zmin) / h;
  return n_z;
}

double calculo_sx(double nx, double xmax, double xmin) {
  double const s_x = (xmax - xmin) / nx;
  return s_x;
}

double calculo_sy(double ny, double ymax, double ymin) {
  double const s_y = (ymax - ymin) / ny;
  return s_y;
}

double calculo_sz(double nz, double zmax, double zmin) {
  double const s_z = (zmax - zmin) / nz;
  return s_z;
}

double calculo_i(double px, double sx, double xmin) {
  double const i_coordinate = (px - xmin) / sx;
  return i_coordinate;
}

double calculo_j(double sy, double py, double ymin) {
  double const j_coordinate = (py - ymin) / sy;
  return j_coordinate;
}

double calculo_k(double sz, double pz, double zmin) {
  double const k_coordinate = (pz - zmin) / sz;
  return k_coordinate;
}

// AQUI NO PUEDES ACCEDER A VARIABLES DEBIDO A QUE ES PRIVADA, SI QUIERES LA HACEMOS PÚBLICA
void incremento_densidades(double h, Particula & particula_i, Particula & particula_j) {
  double const norma = std::pow(particula_i.px - particula_j.px, 2) +
                       std::pow(particula_i.py - particula_j.py, 2) +
                       std::pow(particula_i.pz - particula_j.pz, 2);
  double const h_2 = std::pow(h, 2);
  if (norma < h_2) {
    double const incremento  = std::pow(h_2 - norma, 3);
    particula_i.densidad    += incremento;
    particula_j.densidad    += incremento;
  }
}

// SE PASA DE COMPLEJIDAD
void incremento_aceleracion(Particula & particula_i, Particula & particula_j, double h,
                            double norma, double m) {
  double const operador_izquierda =
      15 * m * std::pow(h - std::pow(std::max(norma, std::pow(10, -12)), 0.5), 2) *
      (particula_i.densidad + particula_j.densidad - 2 * (std::pow(10, -3))) /
      (3.14 * std::pow(h, 6) * std::pow(std::max(norma, std::pow(10, -12)), 0.5));

  double const operador_derecha            = 45 * 0.4 * m / (3.14 * std::pow(h, 6));
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
  particula_i.ac_y += incremento_aceleracion_y;
  particula_j.ac_y += incremento_aceleracion_y;
  particula_i.ac_z += incremento_aceleracion_z;
  particula_j.ac_z += incremento_aceleracion_z;
}

// SI USAS DATOS DE PARTICULA PIENSA SI RENTA MAS TENER ESTA FUNCIÓN DENTRO DE LA CLASE
double transformacion_densidad(double densidad, double h, double m) {
  // SI aqui usas PI, creo que hay una libreria para eso, deberias usarla
  densidad = (densidad + std::pow(h, 6)) * 315 * m / (64 * 3.14 * std::pow(h, 9));
  return densidad;
}

void movimiento_particulas(Particula & particula_i) {
  double const tiempo  = pow(10, -3);
  particula_i.px      += particula_i.hvx * tiempo + particula_i.ax * pow(tiempo, 2);
  particula_i.py      += particula_i.hvy * tiempo + particula_i.ay * pow(tiempo, 2);
  particula_i.pz      += particula_i.hvz * tiempo + particula_i.az * pow(tiempo, 2);
  particula_i.vx       = particula_i.hvx + particula_i.acx * tiempo / 2;
  particula_i.vy       = particula_i.hvy + particula_i.acy * tiempo / 2;
  particula_i.vz       = particula_i.hvz + particula_i.acz * tiempo / 2;
  particula_i.hvx     += particula_i.ax * tiempo;
  particula_i.hvy     += particula_i.ay * tiempo;
  particula_i.hvz     += particula_i.az * tiempo;
}

// EL CUBO DEBERÍA IR EN BLOCK CPP, LEETE LA MEMORIA Y ORDENA LAS COSAS, y si es una clase
// usa el cpp para las funciones y el hpp para la structuración de la clase.
void Cubo {
  int c_x = 0;
  int c_y = 0;
  int c_z = 0;
  void colision_x1(Particula & particula, double xmin, double xmax) {
    if (c_x = 0) {
      double const dx = particula.x - xmin;
      if dx {
        >= 0 {
          return;
        }
      } else {
        particula.x = xmin - dx;
      }
    }
    if (c_x = nx - 1) {
      double const dx = xmax - particula.x;
      if dx {
        >= 0 {
          return;
        }
      } else {
        particula.x = xmax + dx
      }
    }
    particula.vx  = -particula.vx;
    particula.hvx = -particula.hvx
  }
  void colision_y1(Particula & particula, double ymin, double ymax) {
    if (c_y = 0) {
      double const dy = particula.y - ymin;
      if dy {
        >= 0 {
          return;
        }
      } else {
        particula.y = ymin - dy;
      }
    }
    if (c_y = ny - 1) {
      double const dy = ymax - particula.y;
      if dy {
        >= 0 {
          return;
        }
      } else {
        particula.y = ymax + dy
      }
    }
    particula.vy  = -particula.vy;
    particula.hvy = -particula.hvy
  }
  void colision_z1(Particula & particula, double zmin, double zmax) {
    if (c_z = 0) {
      double const dz = particula.z - zmin;
      if dz {
        >= 0 {
          // RETURN EL Q
          return;
        }
      } else {
        particula.z = zmin - dz;
      }
    }
    if (c_z = nz - 1) {
      double const dz = zmax - particula.z;
      if dz {
        >= 0 {
          return;  // MAS DE LO MISMO
        }
      } else {
        particula.z = zmax + dz
      }
    }
    particula.vz  = -particula.vz;
    particula.hvz = -particula.hvz
  }
  void collision_x(class particula, double xmin, double xmax,
                   double h) {                          // o mejor llamar a la funcion nx aqui//
    particula.px    = particula.px + particula.hvx + ;  // delta de t no va a ser 1 siempre?//
    double const nx = calculo_nx(xmin, xmax, h);
    double const dp = std::pow(10, -3);
    double const cs = 3 * std::pow(10, 4);
    double const dv = 128.0 if (c_x = 0) {
      double const incremento_x = dp - x + xmin;
      if incremento { > dp{particula.ac_x += cs * incremento_x - dv * particula.vx}; }
    }
    if (c_x = nx - 1) {
      double const incremento_x = dp - xmax + x;
      if incremento { > dp{particula.ac_x -= cs * incremento_x + dv * particula.vx}; }
    }
  }
  void collision_y(class particula, double ymin, double ymax,
                   double h) {                         // o mejor llamar a la funcion nx aqui//
    double const y  = particula.y + particula.hvy + ;  // delta de t no va a ser 1 siempre?//
    double const ny = calculo_ny(ymin, ymax, h);
    double const dp = std::pow(10, -3);
    double const cs = 3 * std::pow(10, 4);
    double const dv = 128.0 if (c_x = 0) {
      double const incremento_y = dp - y + ymin;
      if incremento { > dp{particula.ac_y += cs * incremento_y - dv * particula.vy}; }
    }
    if (c_y = ny - 1) {
      double const incremento_y = dp - ymax + y;
      if incremento { > dp{particula.ac_y -= cs * incremento_y + dv * particula.vy}; }
    }
  }
  void collision_z(Particula & particula_i, double zmin, double zmax,
                   double h) {                         // o mejor llamar a la funcion nx aqui//
    double const z  = particula.z + particula.hvz + ;  // delta de t no va a ser 1 siempre?//
    double const nz = calculo_nz(zmin, zmax, h);
    double const dp = std::pow(10, -3);
    double const cs = 3 * std::pow(10, 4);
    double const dv = 128.0 if c_z = 0 {
      double const incremento_z = dp - z + zmin;
      if incremento { > dp{particula.ac_z += cs * incremento_z - dv * particula.vz}; }
    }
    if (c_z = nz - 1) {
      double const incremento_z = dp - zmax + z;
      if incremento { > dp{particula.ac_z -= cs * incremento_z + dv * particula.vz}; }
    }
  }
};
