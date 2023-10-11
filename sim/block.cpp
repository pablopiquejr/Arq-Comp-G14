//
// Created by sergio on 3/10/23.
//
#include "block.hpp"
#include "grid.cpp"
#include <iostream>
#include <cmath>

double Bloque::calculo_sx(double nx, double xmax, double xmin) {
  double const s_x = (xmax - xmin) / nx;
  return s_x;
}

double Bloque::calculo_sy(double ny, double ymax, double ymin) {
  double const s_y = (ymax - ymin) / ny;
  return s_y;
}

double Bloque::calculo_sz(double nz, double zmax, double zmin) {
  double const s_z = (zmax - zmin) / nz;
  return s_z;
}


// SI USAS DATOS DE PARTICULA PIENSA SI RENTA MAS TENER ESTA FUNCIÓN DENTRO DE LA CLASE
double Bloque::transformacion_densidad(double densidad, double h, double m) {
  // SI aqui usas PI, creo que hay una libreria para eso, deberias usarla
  densidad = (densidad + std::pow(h, 6)) * 315 * m / (64 * 3.14 * std::pow(h, 9));
  return densidad;
}

void Bloque::movimiento_particulas(Particula & particula_i) {
  double const tiempo  = pow(10, -3);
  particula_i.px      += particula_i.hvx * tiempo + particula_i.acx * pow(tiempo, 2);
  particula_i.py      += particula_i.hvy * tiempo + particula_i.acy * pow(tiempo, 2);
  particula_i.pz      += particula_i.hvz * tiempo + particula_i.acz * pow(tiempo, 2);
  particula_i.vx       = particula_i.hvx + particula_i.acx * tiempo / 2;
  particula_i.vy       = particula_i.hvy + particula_i.acy * tiempo / 2;
  particula_i.vz       = particula_i.hvz + particula_i.acz * tiempo / 2;
  particula_i.hvx     += particula_i.acx * tiempo;
  particula_i.hvy     += particula_i.acy * tiempo;
  particula_i.hvz     += particula_i.acz * tiempo;
}

// AQUI NO PUEDES ACCEDER A VARIABLES DEBIDO A QUE ES PRIVADA, SI QUIERES LA HACEMOS PÚBLICA
void Bloque::incremento_densidades(double h, Particula & particula_i, Particula & particula_j) {
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
  particula_i.acy += incremento_aceleracion_y;
  particula_j.acy += incremento_aceleracion_y;
  particula_i.acz += incremento_aceleracion_z;
  particula_j.acz += incremento_aceleracion_z;
}

void Bloque::colision_x1(Particula &particula, double xmin, double xmax){
  if (s_x==0){
    // Aquí ponía particula.x, supongo que se referia a px
    double const d_x= particula.px-xmin;
    if (d_x<0){
      // Aquí ponía particula.x, supongo que se referia a px
      particula.px=xmin-d_x;
      }
    return;
  }
  // Que es nx????
  if (s_x==nx-1){
    // Aquí ponía particula.x, supongo que se referia a px
    double const d_x= xmax-particula.px;
    if (d_x<0){
      // Aquí ponía particula.x, supongo que se referia a px
      particula.px=xmax+d_x;
      }
    return;
  }
  particula.vx=-particula.vx;
  particula.hvx=-particula.hvx;
}
void Bloque::colision_y1(Particula &particula, double ymin, double ymax){
  if (s_y==0){
    // Aquí ponía particula.y, supongo que se referia a py
    double const d_y= particula.py-ymin;
    if (d_y<0){
      // Aquí ponía particula.y, supongo que se referia a py
      particula.py=ymin-d_y;
      }
      return;
  }
  if (s_y==ny-1){
    // Aquí ponía particula.y, supongo que se referia a py
    double const d_y= ymax-particula.py;
    if (d_y<0) {
      // Aquí ponía particula.y, supongo que se referia a py
      particula.py = ymax + d_y;
    }
    return;
  }
  particula.vy=-particula.vy;
  particula.hvy=-particula.hvy;
}
void Bloque::colision_z1(Particula &particula, double zmin, double zmax){
  if (s_z==0){
    // Aquí ponía particula.z, supongo que se referia a pz
    double const d_z= particula.pz-zmin;
    if (d_z < 0) {
      // Aquí ponía particula.z, supongo que se referia a pz
      particula.pz = zmin - d_z;
    }
    return;
  }

  if (s_z == nz-1){
    // Aquí ponía particula.z, supongo que se referia a pz
    double const d_z= zmax-particula.pz;
    if (d_z < 0){
      // Aquí ponía particula.z, supongo que se referia a pz
      particula.pz=zmax+d_z;
    }
    return;
  }
  particula.vz=-particula.vz;
  particula.hvz=-particula.hvz;
}
//o mejor llamar a la funcion nx aqui//
void Bloque::colision_x(Particula &particula, double xmin, double xmax, double h ) const {
  particula.px    = particula.px + particula.hvx;  // delta de t no va a ser 1 siempre?//
  double const nx = calculo_nx(xmin, xmax, h);
  double const dp = std::pow(10, -3);
  double const cs = 3 * std::pow(10, 4);
  double const dv = 128.0;
  if (s_x == 0) {
    double const incremento_x = dp - x + xmin;
    if (incremento > dp) { particula.acx += cs * incremento_x - dv * particula.vx; }
    if (s_x == nx - 1) {
      double const incremento_x = dp - xmax + x;
      if (incremento > dp) { particula.acx -= cs * incremento_x + dv * particula.vx; }
    }
  }
}
void Bloque::colision_y(Particula & particula, double ymin, double ymax, double h) const {
  particula.py    = particula.py + particula.hvy;  // delta de t no va a ser 1 siempre?//
  double const ny = calculo_ny(ymin, ymax, h);
  double const dp = std::pow(10, -3);
  double const cs = 3 * std::pow(10, 4);
  double const dv = 128.0;
  if (s_x == 0) {
    double const incremento_y = dp - y + ymin;
    if (incremento > dp) { particula.acy += cs * incremento_y - dv * particula.vy; }
  }
  if (s_y == ny - 1) {
    double const incremento_y = dp - ymax + y;
    if (incremento > dp) { particula.acy -= cs * incremento_y + dv * particula.vy; }
  }
}

// o mejor llamar a la funcion nx aqui//
// por que &particula_i?
void Bloque::colision_z(Particula & particula, double zmin, double zmax, double h) const {
  // era double const z
  // Aquí ponía particula.z, supongo que se referia a pz
  particula.pz    = particula.pz + particula.hvz;  // delta de t no va a ser 1 siempre?//
  double const nz = calculo_nz(zmin, zmax, h);
  double const dp = std::pow(10, -3);
  double const cs = 3 * std::pow(10, 4);
  double const dv = 128.0;
  if (s_z == 0) {
    double const incremento_z = dp - z + zmin;
    if (incremento > dp) { particula.acz += cs * incremento_z - dv * particula.vz; };
  }
  if (s_z == nz - 1) {
    double const incremento_z = dp - zmax + z;
    if (incremento > dp) { particula.acz -= cs * incremento_z + dv * particula.vz; };
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