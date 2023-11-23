//
// Created by 34638 on 07/10/2023.
//
#include "../sim/Grid.hpp"
#include "gtest/gtest.h"


namespace {
  TEST(VecBloqueSuite, TestColisionBordes) {
    // Generamos artificialemente 2 partículas de prueba que sabemos que colisionan,
    // y comprobamos nuestros cálculos a mano con calculadora con los que nos da el programa
    Vec_Bloque my_bloque;
    // Partícula en 1234 en el Bloque 3471
    my_bloque.lista_particulas = {0, 2, 40, 100, 281,340, 440, 562, 564,  580, 622 };
    my_bloque.b_x = 0;
    my_bloque.b_y = 0;
    my_bloque.b_z = 0;
    setter struct_test{204, 2};
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
    my_cubo.check_if_repos();
    my_cubo.choques_entre_particulas();
    my_cubo.procesamiento_colisiones();

    // Valores previamente calculados
    EXPECT_EQ(my_cubo.l_m.particulas.a_c[0][0], -2905.5805024307438);
    EXPECT_EQ(my_cubo.l_m.particulas.a_c[0][1], -1565.0798465249659);
    EXPECT_EQ(my_cubo.l_m.particulas.a_c[0][2], 122.90610561474517);
  }
    TEST(VecBloqueSuite, TestRecintoBordes) {
      // Generamos artificialemente 2 partículas de prueba que sabemos que colisionan,
      // y comprobamos nuestros cálculos a mano con calculadora con los que nos da el programa
      Vec_Bloque my_bloque;
      // Partícula en 1234 en el Bloque 3471
      my_bloque.lista_particulas = {0, 2, 40, 100, 281,340, 440, 562, 564,  580, 622 };
      my_bloque.b_x = 0;
      my_bloque.b_y = 0;
      my_bloque.b_z = 0;
      setter struct_test{204, 2};
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
      my_cubo.check_if_repos();
      my_cubo.choques_entre_particulas();
      my_cubo.procesamiento_colisiones();

      // Valores previamente calculados
      EXPECT_EQ(my_cubo.l_m.particulas.pxyz[0][0], -0.060025760021488017);
      EXPECT_EQ(my_cubo.l_m.particulas.hvxyz[0][0], -2.6943693426054187);
      EXPECT_EQ(my_cubo.l_m.particulas.pxyz[0][1], -0.07828968091950439);
      EXPECT_EQ(my_cubo.l_m.particulas.hvxyz[0][1], 1.4466746236322048);
      EXPECT_EQ(my_cubo.l_m.particulas.pxyz[0][2], -0.057518143786095537);
      EXPECT_EQ(my_cubo.l_m.particulas.hvxyz[0][2], 0.26343704948528962);
    }
}