//
// Created by sergio on 4/11/23.
//

#include "vec_block.hpp"

//
// Created by sergio on 3/10/23.
//

void Vec_Bloque::threeD_values(int identifier, std::vector<int> borders) {
  b_z = identifier / (borders[0] * borders[1]);
  b_y = (identifier % (borders[0] * borders[1])) / borders[0];
  b_x = (identifier % (borders[0] * borders[1])) % borders[0];
}

void Vec_Bloque::colision(int n_p, std::vector<Particula> &Lista_b, int eje){
  for (int i_d : lista_particulas) {
    double const const_eje = Lista_b[i_d].pxyz[eje] + Lista_b[i_d].hvxyz[eje] * a_tiempo;
    double incremento_eje;
    if (n_p == 0) {
      incremento_eje = d_p - (const_eje - min[eje]);
    } else {
      incremento_eje = d_p - (max[eje] - const_eje);
    }
    if (incremento_eje > limite_colision) {
      double aumento = s_c * incremento_eje - d_v * Lista_b[i_d].vxyz[eje];
      if (n_p != 0) { aumento = -s_c * incremento_eje - d_v * Lista_b[i_d].vxyz[eje]; }
      Lista_b[i_d].a_c[eje] += aumento;
    }
  }
}

void Vec_Bloque::colision_x(int n_x, std::vector<Particula> & Lista_b) {
  for (int i_d : lista_particulas) {
    double const const_x = Lista_b[i_d].pxyz[0] + Lista_b[i_d].hvxyz[0] * a_tiempo;
    double incremento_x;
    if (n_x == 0) {
      incremento_x = d_p - (const_x - min[0]);
    } else {
      incremento_x = d_p - (max[0] - const_x);
    }
    if (incremento_x > limite_colision) {
      double aumento = s_c * incremento_x - d_v * Lista_b[i_d].vxyz[0];
      if (n_x != 0) { aumento = -s_c * incremento_x - d_v * Lista_b[i_d].vxyz[0]; }
      Lista_b[i_d].a_c[0] += aumento;
    }
  }
}

void Vec_Bloque::colision_y(int n_y, std::vector<Particula> & Lista_b) {
  for (int i_d : lista_particulas) {
    double const const_y = Lista_b[i_d].pxyz[1] + Lista_b[i_d].hvxyz[1] * a_tiempo;
    double incremento_y;
    if (n_y == 0) {
      incremento_y = d_p - (const_y - min[1]);
    } else {
      incremento_y = d_p - (max[1] - const_y);
    }
    if (incremento_y > limite_colision) {
      double aumento = s_c * incremento_y - d_v * Lista_b[i_d].vxyz[1];
      if (n_y != 0) { aumento = -s_c * incremento_y - d_v * Lista_b[i_d].vxyz[1]; }
      Lista_b[i_d].a_c[1] += aumento;
    }
  }
}

void Vec_Bloque::colision_z(int n_z, std::vector<Particula> & Lista_b) {
  for (int i_d : lista_particulas) {
    double const const_z = Lista_b[i_d].pxyz[2] + Lista_b[i_d].hvxyz[2] * a_tiempo;
    double incremento_z;
    if (n_z == 0) {
      incremento_z = d_p - (const_z - min[2]);
    } else {
      incremento_z = d_p - (max[2] - const_z);
    }
    if (incremento_z > limite_colision) {
      double aumento = s_c * incremento_z - d_v * Lista_b[i_d].vxyz[2];
      if (n_z != 0) { aumento = -s_c * incremento_z - d_v * Lista_b[i_d].vxyz[2]; }
      Lista_b[i_d].a_c[2] += aumento;
    }
  }
}

void Vec_Bloque::recinto(int n_x, std::vector<Particula> & Lista_b, int eje) {
  for (int i_d : lista_particulas) {
    double d_eje;
    if (n_x == 0) {
      d_eje = Lista_b[i_d].pxyz[eje] - min[eje];
    } else {
      d_eje = max[eje] - Lista_b[i_d].pxyz[eje];
    }
    if (d_eje < 0) {
      if (n_x == 0) {
        Lista_b[i_d].pxyz[eje] = min[eje] - d_eje;
      } else {
        Lista_b[i_d].pxyz[eje] = max[eje] + d_eje;
      }
      Lista_b[i_d].vxyz[eje]  = -Lista_b[i_d].vxyz[eje];
      Lista_b[i_d].hvxyz[eje] = -Lista_b[i_d].hvxyz[eje];
    }
  }
}

void Vec_Bloque::recinto_x(int n_x, std::vector<Particula> & Lista_b) {
  for (int i_d : lista_particulas) {
    double d_x;
    if (n_x == 0) {
      d_x = Lista_b[i_d].pxyz[0] - min[0];
    } else {
      d_x = max[0] - Lista_b[i_d].pxyz[0];
    }
    if (d_x < 0) {
      if (n_x == 0) {
        Lista_b[i_d].pxyz[0] = min[0] - d_x;
      } else {
        Lista_b[i_d].pxyz[0] = max[0] + d_x;
      }
      Lista_b[i_d].vxyz[0]  = -Lista_b[i_d].vxyz[0];
      Lista_b[i_d].hvxyz[0] = -Lista_b[i_d].hvxyz[0];
    }
  }
}

void Vec_Bloque::recinto_y(int n_y, std::vector<Particula> & Lista_b) {
  for (int i_d : lista_particulas) {
    double d_y;
    if (n_y == 0) {
      d_y = Lista_b[i_d].pxyz[1] - min[1];
    } else {
      d_y = max[1] - Lista_b[i_d].pxyz[1];
    }
    if (d_y < 0) {
      if (n_y == 0) {
        Lista_b[i_d].pxyz[1] = min[1] - d_y;
      } else {
        Lista_b[i_d].pxyz[1] = max[1] + d_y;
      }
      Lista_b[i_d].vxyz[1]  = -Lista_b[i_d].vxyz[1];
      Lista_b[i_d].hvxyz[1] = -Lista_b[i_d].hvxyz[1];
    }
  }
}

void Vec_Bloque::recinto_z(int n_z, std::vector<Particula> & Lista_b) {
  for (int i_d : lista_particulas) {
    double d_z;
    if (n_z == 0) {
      d_z = Lista_b[i_d].pxyz[2] - min[2];
    } else {
      d_z = max[2] - Lista_b[i_d].pxyz[2];
    }
    if (d_z < 0) {
      if (n_z == 0) {
        Lista_b[i_d].pxyz[2] = min[2] - d_z;
      } else {
        Lista_b[i_d].pxyz[2] = max[2] + d_z;
      }
      Lista_b[i_d].vxyz[2]  = -Lista_b[i_d].vxyz[2];
      Lista_b[i_d].hvxyz[2] = -Lista_b[i_d].hvxyz[2];
    }
  }
}

void Vec_Bloque::colision_x_(int n_x, std::vector<Particula> & Lista_b) {
  for (int i_d : lista_particulas) {
    double const const_x = Lista_b[i_d].pxyz[0] + Lista_b[i_d].hvxyz[0] * a_tiempo;
    double incremento_x;
    if (n_x == 0) {
      incremento_x = d_p - (const_x - min[0]);
    } else {
      incremento_x = d_p - (max[0] - const_x);
    }
    if (incremento_x > limite_colision) {
      double aumento = s_c * incremento_x - d_v * Lista_b[i_d].vxyz[0];
      if (n_x != 0) { aumento = -s_c * incremento_x - d_v * Lista_b[i_d].vxyz[0]; }
      Lista_b[i_d].a_c[0] += aumento;
    }
    Lista_b[i_d].movimiento_particulas();
    double d_x;
    if (n_x == 0) {
      d_x = Lista_b[i_d].pxyz[0] - min[0];
    } else {
      d_x = max[0] - Lista_b[i_d].pxyz[0];
    }
    if (d_x < 0) {
      if (n_x == 0) {
        Lista_b[i_d].pxyz[0] = min[0] - d_x;
      } else {
        Lista_b[i_d].pxyz[0] = max[0] + d_x;
      }
      Lista_b[i_d].vxyz[0]  = -Lista_b[i_d].vxyz[0];
      Lista_b[i_d].hvxyz[0] = -Lista_b[i_d].hvxyz[0];
    }
  }
}

void Vec_Bloque::colision_y_(int n_y, std::vector<Particula> & Lista_b) {
  for (int i_d : lista_particulas) {
    double const const_y = Lista_b[i_d].pxyz[1] + Lista_b[i_d].hvxyz[1] * a_tiempo;
    double incremento_y;
    if (n_y == 0) {
      incremento_y = d_p - (const_y - min[1]);
    } else {
      incremento_y = d_p - (max[1] - const_y);
    }
    if (incremento_y > limite_colision) {
      double aumento = s_c * incremento_y - d_v * Lista_b[i_d].vxyz[1];
      if (n_y != 0) { aumento = -s_c * incremento_y - d_v * Lista_b[i_d].vxyz[1]; }
      Lista_b[i_d].a_c[1] += aumento;
    }
    Lista_b[i_d].movimiento_particulas();
    double d_y;
    if (n_y == 0) {
      d_y = Lista_b[i_d].pxyz[1] - min[1];
    } else {
      d_y = max[1] - Lista_b[i_d].pxyz[1];
    }
    if (d_y < 0) {
      if (n_y == 0) {
        Lista_b[i_d].pxyz[1] = min[1] - d_y;
      } else {
        Lista_b[i_d].pxyz[1] = max[1] + d_y;
      }
      Lista_b[i_d].vxyz[1]  = -Lista_b[i_d].vxyz[1];
      Lista_b[i_d].hvxyz[1] = -Lista_b[i_d].hvxyz[1];
    }
  }
}

void Vec_Bloque::colision_z_(int n_z, std::vector<Particula> & Lista_b) {
  for (int i_d : lista_particulas) {
    double const const_z = Lista_b[i_d].pxyz[2] + Lista_b[i_d].hvxyz[2] * a_tiempo;
    double incremento_z = d_p - (const_z - min[2]);
    if (n_z != 0) {
      incremento_z = d_p - (max[2] - const_z);
    }
    if (incremento_z > limite_colision) {
      double aumento = s_c * incremento_z - d_v * Lista_b[i_d].vxyz[2];
      if (n_z != 0) { aumento = -s_c * incremento_z - d_v * Lista_b[i_d].vxyz[2]; }
      Lista_b[i_d].a_c[2] += aumento;
    }
    Lista_b[i_d].movimiento_particulas();
    double d_z = Lista_b[i_d].pxyz[2] - min[2];;
    if (n_z != 0) {
      d_z = max[2] - Lista_b[i_d].pxyz[2];
    }
    if (d_z < 0) {
      if (n_z == 0) {
        Lista_b[i_d].pxyz[2] = min[2] - d_z;
      } else {
        Lista_b[i_d].pxyz[2] = max[2] + d_z;
      }
      Lista_b[i_d].vxyz[2]  = -Lista_b[i_d].vxyz[2];
      Lista_b[i_d].hvxyz[2] = -Lista_b[i_d].hvxyz[2];
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