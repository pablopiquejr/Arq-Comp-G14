//
// Created by sergio on 3/10/23.
//
#include "block.hpp"


// SI USAS DATOS DE PARTICULA PIENSA SI RENTA MAS TENER ESTA FUNCIÓN DENTRO DE LA CLASE
double Bloque::transformacion_densidad(Particula & particula) {
  // SI aqui usas PI, creo que hay una libreria para eso, deberias usarla
  particula.densidad = (particula.densidad + std::pow(h_logitud_suavizado, 6)) *
                       315 * m_particula / (64 * std::numbers::pi * std::pow(h_logitud_suavizado, 9));
}

void Bloque::movimiento_particulas(Particula & particula_i) {
  double const tiempo  = std::pow(10, -3);
  particula_i.px      += particula_i.hvx * tiempo + particula_i.acx * pow(tiempo, 2);
  particula_i.py      += particula_i.hvy * tiempo + particula_i.acy * pow(tiempo, 2);
  particula_i.pz      += particula_i.hvz * tiempo + particula_i.acz * pow(tiempo, 2);
  // se puede cambiar la división por * 0.5
  particula_i.vx       = particula_i.hvx + particula_i.acx * tiempo * 2;
  particula_i.vy       = particula_i.hvy + particula_i.acy * tiempo / 2;
  particula_i.vz       = particula_i.hvz + particula_i.acz * tiempo / 2;
  particula_i.hvx     += particula_i.acx * tiempo;
  particula_i.hvy     += particula_i.acy * tiempo;
  particula_i.hvz     += particula_i.acz * tiempo;
}


void Bloque::incremento_densidades(Particula & particula_i, Particula & particula_j) {
  double const norma = std::pow(particula_i.px - particula_j.px, 2) +
                       std::pow(particula_i.py - particula_j.py, 2) +
                       std::pow(particula_i.pz - particula_j.pz, 2);
  double const h_2 = std::pow(h_logitud_suavizado, 2);
  if (norma < h_2) {
    double const incremento  = std::pow(h_2 - norma, 3);
    particula_i.densidad    += incremento;
    particula_j.densidad    += incremento;
  }
  incremento_aceleracion(particula_i, particula_j,norma);
}


// SE PASA DE COMPLEJIDAD
void Bloque::incremento_aceleracion(Particula & particula_i, Particula & particula_j, double norma) {
  double const operador_izquierda =
      // el 1.5 es 3/2
      15 * m_particula * 1.5 * p_s * std::pow(h_logitud_suavizado - std::pow(std::max(norma, std::pow(10, -12)), 0.5), 2) *
      (particula_i.densidad + particula_j.densidad - 2 * (std::pow(10, -3))) /
      (std::numbers::pi  * std::pow(h_logitud_suavizado, 6) * std::pow(std::max(norma, std::pow(10, -12)), 0.5));

  double const operador_derecha = 45 * 0.4 * m_particula / (std::numbers::pi  * std::pow(h_logitud_suavizado, 6));
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

void Bloque::colision_x1(Particula &particula, Cubo &cubo){
  if (b_x_coordinate==0){
    // Aquí ponía particula.x, supongo que se referia a px
    double const d_x= particula.px-x_min;
    if (d_x<0){
      // Aquí ponía particula.x, supongo que se referia a px
      particula.px=x_min-d_x;
      }
    return;
  }
  // Que es n_x????
  if (b_x_coordinate==cubo.n_x-1){
    // Aquí ponía particula.x, supongo que se referia a px
    double const d_x= x_max-particula.px;
    if (d_x<0){
      // Aquí ponía particula.x, supongo que se referia a px
      particula.px=x_max+d_x;
      }
    return;
  }
  particula.vx=-particula.vx;
  particula.hvx=-particula.hvx;
}
void Bloque::colision_y1(Particula &particula, Cubo &cubo){
  if (b_y_coordinate==0){
    // Aquí ponía particula.y, supongo que se referia a py
    double const d_y= particula.py-y_min;
    if (d_y<0){
      // Aquí ponía particula.y, supongo que se referia a py
      particula.py=y_min-d_y;
      }
      return;
  }
  if (b_y_coordinate==cubo.n_y-1){
    // Aquí ponía particula.y, supongo que se referia a py
    double const d_y= y_max-particula.py;
    if (d_y<0) {
      // Aquí ponía particula.y, supongo que se referia a py
      particula.py = y_max + d_y;
    }
    return;
  }
  particula.vy=-particula.vy;
  particula.hvy=-particula.hvy;
}
void Bloque::colision_z1(Particula &particula, Cubo &cubo){
  if (b_z_coordinate==0){
    // Aquí ponía particula.z, supongo que se referia a pz
    double const d_z= particula.pz-z_min;
    if (d_z < 0) {
      // Aquí ponía particula.z, supongo que se referia a pz
      particula.pz = z_min - d_z;
    }
    return;
  }

  if (b_z_coordinate == cubo.n_z-1){
    // Aquí ponía particula.z, supongo que se referia a pz
    double const d_z= z_max-particula.pz;
    if (d_z < 0){
      // Aquí ponía particula.z, supongo que se referia a pz
      particula.pz=z_max+d_z;
    }
    return;
  }
  particula.vz=-particula.vz;
  particula.hvz=-particula.hvz;
}
//TEN EN CUENTA QUE ESTO ES PARTE DE LA FUNCION BLOQUE, NO TIENE n_x
void Bloque::colision_x(Particula &particula, Cubo &cubo) {
  particula.px = particula.px + particula.hvx * a_tiempo;  // delta de t no va a ser 1 siempre?//

  if (b_x_coordinate == 0) {
    double const incremento_x = d_p - particula.px + x_min;
    if (incremento_x > d_p) { particula.acx += s_c * incremento_x - d_v * particula.vx; }
    if (b_y_coordinate == cubo.n_x - 1) {
      double const incremento_x = d_p - x_max + particula.px;
      if (incremento_x > d_p) { particula.acx -= s_c * incremento_x + d_v * particula.vx; }
    }
  }
}
void Bloque::colision_y(Particula & particula, Cubo &cubo) {
  particula.py    = particula.py + particula.hvy * a_tiempo;  // delta de t no va a ser 1 siempre?//

  if (b_y_coordinate == 0) {
    double const incremento_y = d_p - particula.py + y_min;
    if (incremento_y > d_p) { particula.acy += s_c * incremento_y - d_v * particula.vy; }
  }
  if (b_y_coordinate == cubo.n_y - 1) {
    double const incremento_y = d_p - y_max + particula.py;
    if (incremento_y > d_p) { particula.acy -= s_c * incremento_y + d_v * particula.vy; }
  }
}

// o mejor llamar a la funcion n_x aqui//
// por que &particula_i?
void Bloque::colision_z(Particula & particula, Cubo &cubo) {
  // era double const z
  // Aquí ponía particula.z, supongo que se referia a pz
  particula.pz    = particula.pz + particula.hvz * a_tiempo;  // delta de t no va a ser 1 siempre?//

  if (b_z_coordinate == 0) {
    double const incremento_z = d_p - particula.pz + z_min;
    if (incremento_z > d_p) { particula.acz += s_c * incremento_z - d_v * particula.vz; };
  }
  if (b_z_coordinate == cubo.n_z - 1) {
    double const incremento_z = d_p - z_max + particula.pz;
    if (incremento_z > d_p) { particula.acz -= s_c * incremento_z + d_v * particula.vz; };
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