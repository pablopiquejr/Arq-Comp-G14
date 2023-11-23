#include "../sim/vec_grid.hpp"
#include <cmath>
#include "gtest/gtest.h"

namespace {

  TEST(GridTestSuite, TestReposicionamientoParticulas) {
    // Partícula en 1234 en el Bloque 3471
    Vec_Bloque my_bloque;
    // Partícula en 1234 en el Bloque 3471
    my_bloque.threeD_values(3471, {15, 21, 15});
    longitud_y_masa struct_test{204, 1};
    struct_test.particulas.pxyz = {
      {-0.040281, -0.0650672, 0.00368461}
    };
    struct_test.particulas.hvxyz = {
      {-31.6856, 21.8196, -29.2818}
    };
    struct_test.particulas.vxyz = {
      {-13.6254, 7.78405, -10.9486}
    };
    struct_test.particulas.densidad = {0};
    struct_test.particulas.a_c = {
      {-36120.4, -28071, -36666.4}
    };
    struct_test.particulas.bpos = {
      {my_bloque.b_x, my_bloque.b_y, my_bloque.b_z}
    };

    Grid my_cubo(struct_test);
    Vec_Bloque my_bloque2;
    my_cubo.primeros_calculos();

    // generamos los b_x, b_y, b_z de la partícula 1234 en el bloque 2222
    // para autorizarlo en el EXPECTED
    my_bloque2.threeD_values(2222, my_cubo.borders);
    my_cubo.check_if_repos();

    EXPECT_EQ(struct_test.particulas.bpos[0][0],  my_bloque.b_x);
    EXPECT_EQ(struct_test.particulas.bpos[0][1], my_bloque.b_y);
    EXPECT_EQ(struct_test.particulas.bpos[0][2], my_bloque.b_z);
  }

  TEST(GridTestSuite, TestIniciarAceleraciones) {
    Vec_Bloque my_bloque;
    // Partícula en 1234 en el Bloque 3471
    my_bloque.threeD_values(3471, {15, 21, 15});
    longitud_y_masa struct_test{204, 1};
    struct_test.particulas.pxyz = {
      {-0.040281, -0.0650672, 0.00368461}
    };
    struct_test.particulas.hvxyz = {
      {-31.6856, 21.8196, -29.2818}
    };
    struct_test.particulas.vxyz = {
      {-13.6254, 7.78405, -10.9486}
    };
    struct_test.particulas.densidad = {0};
    struct_test.particulas.a_c = {
      {-36120.4, -28071, -36666.4}
    };
    struct_test.particulas.bpos = {
      {my_bloque.b_x, my_bloque.b_y, my_bloque.b_z}
    };

    Grid my_cubo(struct_test);
    my_cubo.primeros_calculos();
    my_cubo.check_if_repos();
    EXPECT_EQ(my_cubo.l_m.particulas.a_c[0][0],  0);
    EXPECT_EQ(my_cubo.l_m.particulas.a_c[0][1], -9.8);
    EXPECT_EQ(my_cubo.l_m.particulas.a_c[0][2], 0);
  }

  TEST(GridTestSuite, TestIncrementoDensidades) {
    // Generamos artificialemente 2 partículas de prueba que sabemos que colisionan,
    // y comprobamos nuestros cálculos a mano con calculadora con los que nos da el programa
    Vec_Bloque my_bloque;
    // Partícula en 1234 en el Bloque 3471
    longitud_y_masa struct_test{204, 2};
    struct_test.particulas.pxyz = {
      {-0.057331390678882599, -0.080263644456863403, -0.057781580835580826},
      { -0.064884483814239502, -0.077343977987766266, -0.058011941611766815}

    };
    struct_test.particulas.hvxyz = {
      { 0.21121115982532501, 0.11840522289276123,0.14053094387054443},
      {0.065619014203548431, 0.036966234445571899, 0.14385625720024109}

    };
    struct_test.particulas.vxyz = {
      {0.21360234916210175, 0.12304694205522537,  0.13833959400653839},
      { 0.067155852913856506, 0.044741451740264893, 0.14454919099807739}

    };
    struct_test.particulas.densidad = {0, 0};
    struct_test.particulas.a_c = {
      {0, -9.8000000000000007, 0},
      {0, -9.8000000000000007, 0}
    };
    struct_test.particulas.bpos = {
      {0, 0, 0},
      {0, 0, 0}
    };

    Grid my_cubo(struct_test);
    my_cubo.primeros_calculos();
    // Valores previamente calculados
    my_cubo.incremento_densidad(6.9036548442906562e-05,  6.562673428935073e-05,0, 1);
    EXPECT_EQ(my_cubo.l_m.particulas.densidad[0], 3.9645338230214257e-17);
    EXPECT_EQ(my_cubo.l_m.particulas.densidad[1], 3.9645338230214257e-17);
  }
  TEST(GridTestSuite, TestTransformacionDensidades) {
    // Generamos artificialemente 2 partículas de prueba que sabemos que colisionan,
    // y comprobamos nuestros cálculos a mano con calculadora con los que nos da el programa
    Vec_Bloque my_bloque;
    // Partícula en 1234 en el Bloque 3471
    longitud_y_masa struct_test{204, 2};
    struct_test.particulas.pxyz = {
      {-0.057331390678882599, -0.080263644456863403, -0.057781580835580826},
      { -0.064884483814239502, -0.077343977987766266, -0.058011941611766815}

    };
    struct_test.particulas.hvxyz = {
      { 0.21121115982532501, 0.11840522289276123,0.14053094387054443},
      {0.065619014203548431, 0.036966234445571899, 0.14385625720024109}

    };
    struct_test.particulas.vxyz = {
      {0.21360234916210175, 0.12304694205522537,  0.13833959400653839},
      { 0.067155852913856506, 0.044741451740264893, 0.14454919099807739}

    };
    struct_test.particulas.densidad = {0, 0};
    struct_test.particulas.a_c = {
      {0, -9.8000000000000007, 0},
      {0, -9.8000000000000007, 0}
    };
    struct_test.particulas.bpos = {
      {0, 0, 0},
      {0, 0, 0}
    };

    Grid my_cubo(struct_test);
    my_cubo.primeros_calculos();
    // Valores previamente calculados
    my_cubo.choques_entre_particulas();
    EXPECT_EQ(my_cubo.l_m.particulas.densidad[0], 321.75397796532849);
    EXPECT_EQ(my_cubo.l_m.particulas.densidad[1], 321.75397796532849);
  }
  TEST(GridTestSuite, TestTranferenciaAceleraciones) {
    // Generamos artificialemente 2 partículas de prueba que sabemos que colisionan,
    // y comprobamos nuestros cálculos a mano con calculadora con los que nos da el programa
    Vec_Bloque my_bloque;
    // Partícula en 1234 en el Bloque 3471
    longitud_y_masa struct_test{204, 2};
    struct_test.particulas.pxyz = {
      {-0.057331390678882599, -0.080263644456863403, -0.057781580835580826},
      { -0.064884483814239502, -0.077343977987766266, -0.058011941611766815}

    };
    struct_test.particulas.hvxyz = {
      { 0.21121115982532501, 0.11840522289276123,0.14053094387054443},
      {0.065619014203548431, 0.036966234445571899, 0.14385625720024109}

    };
    struct_test.particulas.vxyz = {
      {0.21360234916210175, 0.12304694205522537,  0.13833959400653839},
      { 0.067155852913856506, 0.044741451740264893, 0.14454919099807739}

    };
    struct_test.particulas.densidad = {321.75397796532849, 321.75397796532849};
    struct_test.particulas.a_c = {
      {0, -9.8000000000000007, 0},
      {0, -9.8000000000000007, 0}
    };
    struct_test.particulas.bpos = {
      {0, 0, 0},
      {0, 0, 0}
    };

    Grid my_cubo(struct_test);
    my_cubo.primeros_calculos();
    my_cubo.transferencia_aceleracion();
    // Valores previamente calculados
    EXPECT_EQ(my_cubo.l_m.particulas.a_c[0][0],  -2905.5805024307438);
    EXPECT_EQ(my_cubo.l_m.particulas.a_c[0][1], -1559.6870149610163);
    EXPECT_EQ(my_cubo.l_m.particulas.a_c[0][2], 122.90610561474517);
  }

  TEST(GridTestSuite, TestMovimientoParticulas) {
        // Generamos artificialemente 2 partículas de prueba que sabemos que colisionan,
        // y comprobamos nuestros cálculos a mano con calculadora con los que nos da el programa
        Vec_Bloque my_bloque;
        // Partícula en 1234 en el Bloque 3471
        longitud_y_masa struct_test{204, 2};
        struct_test.particulas.pxyz = {
          {-0.057331390678882599, -0.080263644456863403, -0.057781580835580826},
          { -0.064884483814239502, -0.077343977987766266, -0.058011941611766815}

        };
        struct_test.particulas.hvxyz = {
          { 0.21121115982532501, 0.11840522289276123,0.14053094387054443},
          {0.065619014203548431, 0.036966234445571899, 0.14385625720024109}

        };
        struct_test.particulas.vxyz = {
          {0.21360234916210175, 0.12304694205522537,  0.13833959400653839},
          { 0.067155852913856506, 0.044741451740264893, 0.14454919099807739}

        };
        struct_test.particulas.densidad = {0, 0};
        struct_test.particulas.a_c = {
          {0, -9.8000000000000007, 0},
          {0, -9.8000000000000007, 0}
        };
        struct_test.particulas.bpos = {
          {0, 0, 0},
          {0, 0, 0}
        };

        Grid my_cubo(struct_test);
        my_cubo.primeros_calculos();
        my_cubo.procesamiento_colisiones();
        my_cubo.transferencia_aceleracion();
        // Valores previamente calculados
        EXPECT_EQ(my_cubo.l_m.particulas.pxyz[0][0], -0.057120179519057276);
        EXPECT_EQ(my_cubo.l_m.particulas.pxyz[0][1], -0.079839567934465408);
  }
}