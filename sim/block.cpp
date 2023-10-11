//
// Created by sergio on 3/10/23.
//
#include "block.hpp"

double Bloque::calculo_sx(double nx, double xmax, double xmin) {
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
void Bloque::incremento_aceleracion(Particula & particula_i, Particula & particula_j, double h,
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


void Bloque::colision_x1(Particula & particula, double xmin, double xmax) {
    if (s_x = 0) {
        double const dx = particula.x - xmin;
        if dx {
                    >= 0 {
                        return;
                    }
            } else {
            particula.x = xmin - dx;
        }
    }
    if (s_x = nx - 1) {
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
void Bloque::colision_y1(Particula & particula, double ymin, double ymax) {
    if (s_y = 0) {
        double const dy = particula.y - ymin;
        if dy {
                    >= 0 {
                        return;
                    }
            } else {
            particula.y = ymin - dy;
        }
    }
    if (s_y = ny - 1) {
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
void Bloque::colision_z1(Particula & particula, double zmin, double zmax) {
    if (s_z = 0) {
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
    if (s_z = nz - 1) {
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
void Bloque::colision_x(class particula, double xmin, double xmax,double h) {                          // o mejor llamar a la funcion nx aqui//
    particula.px    = particula.px + particula.hvx + ;  // delta de t no va a ser 1 siempre?//
    double const nx = calculo_nx(xmin, xmax, h);
    double const dp = std::pow(10, -3);
    double const cs = 3 * std::pow(10, 4);
    double const dv = 128.0 if (s_x = 0) {
        double const incremento_x = dp - x + xmin;
        if incremento { > dp{particula.ac_x += cs * incremento_x - dv * particula.vx}; }
    }
    if (s_x = nx - 1) {
        double const incremento_x = dp - xmax + x;
        if incremento { > dp{particula.ac_x -= cs * incremento_x + dv * particula.vx}; }
    }
}
void Bloque::colision_y(class particula, double ymin, double ymax,
                 double h) {                         // o mejor llamar a la funcion nx aqui//
    double const y  = particula.y + particula.hvy + ;  // delta de t no va a ser 1 siempre?//
    double const ny = calculo_ny(ymin, ymax, h);
    double const dp = std::pow(10, -3);
    double const cs = 3 * std::pow(10, 4);
    double const dv = 128.0 if (s_x = 0) {
        double const incremento_y = dp - y + ymin;
        if incremento { > dp{particula.ac_y += cs * incremento_y - dv * particula.vy}; }
    }
    if (s_y = ny - 1) {
        double const incremento_y = dp - ymax + y;
        if incremento { > dp{particula.ac_y -= cs * incremento_y + dv * particula.vy}; }
    }
}
void Bloque::colision_z(Particula & particula_i, double zmin, double zmax,
                 double h) {                         // o mejor llamar a la funcion nx aqui//
    double const z  = particula.z + particula.hvz + ;  // delta de t no va a ser 1 siempre?//
    double const nz = calculo_nz(zmin, zmax, h);
    double const dp = std::pow(10, -3);
    double const cs = 3 * std::pow(10, 4);
    double const dv = 128.0 if s_z = 0 {
        double const incremento_z = dp - z + zmin;
        if incremento { > dp{particula.ac_z += cs * incremento_z - dv * particula.vz}; }
    }
    if (s_z = nz - 1) {
        double const incremento_z = dp - zmax + z;
        if incremento { > dp{particula.ac_z -= cs * incremento_z + dv * particula.vz}; }
    }
}

/////////////////EJEMPLO DE COMO SE PROGRAMAN LOS TESTS ///////////////////////////

/*#include "block.hpp"
#include "product.h"
#include <gtest/gtest.h>

// https://google.github.io/googletest/reference/assertions.html

namespace
{
    TEST(PersonTestSuite, functionA)
{
    Product p;
    EXPECT_EQ(p.computeA(10, 20), 200);
}
TEST(PersonTestSuite, functionB)
{
Product p;
EXPECT_EQ(p.computeB(10, 20, 30), 6000);
}

TEST(PersonTestSuite, not_equal_functionB)
{
Product p;
EXPECT_NE(p.computeB(10, 20, 30), 5000);
}

TEST(PersonTestSuite, fun_B_greater_funA)
{
Product p;
EXPECT_GT(p.computeB(10, 20, 30), p.computeA(10, 10));
}

}
 */