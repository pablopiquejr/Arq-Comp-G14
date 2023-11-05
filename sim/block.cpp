//
// Created by sergio on 3/10/23.
//
#include "block.hpp"

Bloque::Bloque(int param_x, int param_y, int param_z) : b_x(param_x), b_y(param_y), b_z(param_z) { }

void Bloque::colision_x(int n_x) {
  for (Particula & particula : lista_particulas) {
    double const const_x = particula.pxyz[0] + particula.hvxyz[0] * a_tiempo;
    double incremento_x;
    if (n_x == 0) {
      incremento_x = d_p - (const_x - min[0]);
    } else {
      incremento_x = d_p - (max[0] - const_x);
    }
    if (incremento_x > limite_colision) {
      double aumento = s_c * incremento_x - d_v * particula.vxyz[0];
      if (n_x != 0) { aumento *= -1; }
      particula.a_c[0] += aumento;
    }
  }
}

void Bloque::colision_y(int n_y) {
  for (Particula & particula : lista_particulas) {
    double const const_y = particula.pxyz[1] + particula.hvxyz[1] * a_tiempo;
    double incremento_y;
    if (n_y == 0) {
      incremento_y = d_p - (const_y - min[1]);
    } else {
      incremento_y = d_p - (max[1] - const_y);
    }
    if (incremento_y > limite_colision) {
      double aumento = s_c * incremento_y - d_v * particula.vxyz[1];
      if (n_y != 0) { aumento *= -1; }
      particula.a_c[1] += aumento;
    }
  }
}

void Bloque::colision_z(int n_z) {
  for (Particula & particula : lista_particulas) {
    double const const_z = particula.pxyz[2] + particula.hvxyz[2] * a_tiempo;
    double incremento_z;
    if (n_z == 0) {
      incremento_z = d_p - (const_z - min[2]);
    } else {
      incremento_z = d_p - (max[2] - const_z);
    }
    if (incremento_z > limite_colision) {
      double aumento = s_c * incremento_z - d_v * particula.vxyz[2];
      if (n_z != 0) { aumento *= -1; }
      particula.a_c[2] += aumento;
    }
  }
}

void Bloque::recinto_x(int n_x) {
  for (Particula & particula : lista_particulas) {
    double d_x;
    if (n_x == 0) {
      d_x = particula.pxyz[0] - min[0];
    } else {
      d_x = max[0] - particula.pxyz[0];
    }
    if (d_x < 0) {
      if (n_x == 0) {
        particula.pxyz[0] = min[0] - d_x;
      } else {
        particula.pxyz[0] = max[0] + d_x;
      }
      particula.vxyz[0]  = -particula.vxyz[0];
      particula.hvxyz[0] = -particula.hvxyz[0];
    }
  }
}

void Bloque::recinto_y(int n_y) {
  for (Particula &particula : lista_particulas) {
    double d_y;
    if (n_y == 0) {
      d_y = particula.pxyz[1] - min[1];
    } else {
      d_y = max[1] - particula.pxyz[1];
    }
    if (d_y < 0) {
      if (n_y == 0) {
        particula.pxyz[1] = min[1] - d_y;
      } else {
        particula.pxyz[1] = max[1] + d_y;
      }
      particula.vxyz[1]  = -particula.vxyz[1];
      particula.hvxyz[1] = -particula.hvxyz[1];
    }
  }
}

void Bloque::recinto_z(int n_z) {
  for (Particula &particula : lista_particulas) {
    double d_z;
    if (n_z == 0) {
      d_z = particula.pxyz[2] - min[2];
    } else {
      d_z = max[2] - particula.pxyz[2];
    }
    if (d_z < 0) {
      if (n_z == 0) {
        particula.pxyz[2] = min[2] - d_z;
      } else {
        particula.pxyz[2] = max[2] + d_z;
      }
      particula.vxyz[2]  = -particula.vxyz[2];
      particula.hvxyz[2] = -particula.hvxyz[2];
    }
  }
}


void Bloque::colision_x_baja() {
  for (Particula &particula : lista_particulas) {
    double const const_x      = particula.pxyz[0] + particula.hvxyz[0] * a_tiempo;
    double const incremento_x = d_p - (const_x - min[0]);
    if (incremento_x > limite_colision) {
      particula.a_c[0] += s_c * incremento_x - d_v * particula.vxyz[0];
    }
    particula.movimiento_particulas();
    double const d_x = particula.pxyz[0] - min[0];
    if (d_x < 0) {
      particula.pxyz[0]  = min[0] - d_x;
      particula.vxyz[0]  = -particula.vxyz[0];
      particula.hvxyz[0] = -particula.hvxyz[0];
    }
  }
}

void Bloque::colision_y_baja() {
  for (Particula &particula : lista_particulas) {
    double const const_y      = particula.pxyz[1] + particula.hvxyz[1] * a_tiempo;
    double const incremento_y = d_p - const_y + min[1];
    if (incremento_y > limite_colision) {
      particula.a_c[0] += s_c * incremento_y - d_v * particula.vxyz[1];
    }
    particula.movimiento_particulas();
    double const d_y = particula.pxyz[1] - min[1];
    if (d_y < 0) {
      particula.pxyz[1]  = min[1] - d_y;
      particula.vxyz[1]  = -particula.vxyz[1];
      particula.hvxyz[1] = -particula.hvxyz[1];
    }
  }
}

void Bloque::colision_z_baja() {
  for (Particula &particula : lista_particulas) {
    double const const_z =
        particula.pxyz[2] + particula.hvxyz[2] * a_tiempo;  // delta de t no va a ser 1 siempre?//
    double const incremento_z = d_p - const_z + min[2];
    if (incremento_z > limite_colision) {
      particula.a_c[0] += s_c * incremento_z - d_v * particula.vxyz[2];
    }
    particula.movimiento_particulas();
    double const d_z = particula.pxyz[2] - min[2];
    if (d_z < 0) {
      particula.pxyz[2]  = min[2] - d_z;
      particula.vxyz[2]  = -particula.vxyz[2];
      particula.hvxyz[2] = -particula.hvxyz[2];
    }
  }
}

void Bloque::colision_x_alta() {
  for (Particula &particula : lista_particulas) {
    double const const_x =
        particula.pxyz[0] + particula.hvxyz[0] * a_tiempo;  // delta de t no va a ser 1 siempre?//
    double const incremento_x = d_p - max[0] + const_x;
    if (incremento_x > limite_colision) {
      particula.a_c[0] += -s_c * incremento_x + d_v * particula.vxyz[0];
    }
    particula.movimiento_particulas();
    double const d_x = max[0] - particula.pxyz[0];
    if (d_x < 0) {
      particula.pxyz[0]  = max[0] + d_x;
      particula.vxyz[0]  = -particula.vxyz[0];
      particula.hvxyz[0] = -particula.hvxyz[0];
    }
  }
}

void Bloque::colision_y_alta() {
  for (Particula &particula : lista_particulas) {
    double const const_y =
        particula.pxyz[1] + particula.hvxyz[1] * a_tiempo;  // delta de t no va a ser 1 siempre?//
    double const incremento_y = d_p - max[1] + const_y;
    if (incremento_y > limite_colision) {
      particula.a_c[0] += -s_c * incremento_y + d_v * particula.vxyz[1];
    }
    particula.movimiento_particulas();
    double const d_y = max[1] - particula.pxyz[1];
    if (d_y < 0) {
      particula.pxyz[1]  = max[1] + d_y;
      particula.vxyz[1]  = -particula.vxyz[1];
      particula.hvxyz[1] = -particula.hvxyz[1];
    }
  }
}

void Bloque::colision_z_alta() {
  for (Particula &particula : lista_particulas) {
    double const const_z =
        particula.pxyz[2] + particula.hvxyz[2] * a_tiempo;  // delta de t no va a ser 1 siempre?//
    double const incremento_z = d_p - max[2] + const_z;
    if (incremento_z > limite_colision) {
      particula.a_c[0] += -s_c * incremento_z + d_v * particula.vxyz[2];
    }
    particula.movimiento_particulas();
    double const d_z = max[2] - particula.pxyz[2];
    if (d_z < 0) {
      particula.pxyz[2]  = max[2] + d_z;
      particula.vxyz[2]  = -particula.vxyz[2];
      particula.hvxyz[2] = -particula.hvxyz[2];
    }
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