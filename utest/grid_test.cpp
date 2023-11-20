#include "../sim/vec_grid.cpp"
#include "../sim/progargs.cpp"
#include "gtest/gtest.h"

namespace {

  TEST(GridTestSuite, TestReposicionamientoParticulas) {
    // Comparar iteración anterior con iteración actual particula 4312
    Particula particula;
    // Iteración 3:
    // Instancia de Particula en iteración 3
    particula.pxyz = {
      {0.0638389, -0.0495847, 0.000251098}
    };
    particula.hvxyz = {
      {-0.660175, 15.1248, -19.2416}
    };
    particula.vxyz = {
      {-0.272216, 6.75671, -8.69694}
    };
    particula.densidad = {0};
    particula.a_c = {
      {0, -9.8, 0}
    };
    longitud_y_masa struct_test{204.0f, 4800};
    struct_test.particulas.pxyz = {
      {-0.0123631, -0.0815473, 0.0266473}
    };
    struct_test.particulas.hvxyz = {
      { 0.0717484, 0.0139219, 0.108199}
    };
    struct_test.particulas.vxyz = {
      {0.0653556, 0.0152707, 0.112494}
    };
    struct_test.particulas.densidad = {0};
    struct_test.particulas.a_c = {
      {0, -9.8, 0}
    };
    struct_test.particulas.bpos = {
      {1, 0, 0}
    };

    Grid my_cubo(struct_test);
    my_cubo.primeros_calculos();
    my_cubo.check_if_repos();
    // Expect con pxyz de iteración 4 de las trazas repos 4312
    EXPECT_EQ(particula.pxyz[1234][0],  -0.183957);
    EXPECT_EQ(particula.pxyz[1234][1], -0.0652598);
    EXPECT_EQ(particula.pxyz[1234][2], 0.309228);
  }

  TEST(GridTestSuite, TestIniciarAceleraciones) {
    Particula particula;
    particula.pxyz = {
      {0.0638389, -0.0495847, 0.000251098},
      {}
    };
    particula.hvxyz = {
      {-0.660175, 15.1248, -19.2416}
    };
    particula.vxyz = {
      {-0.272216, 6.75671, -8.69694}
    };
    particula.densidad = {0};
    particula.a_c = {
      {0, -9.8, 0}
    };
    longitud_y_masa struct_test{204.0f, 4800};
    struct_test.particulas.pxyz = {
      {-0.0123631, -0.0815473, 0.0266473}
    };
    struct_test.particulas.hvxyz = {
      { 0.0717484, 0.0139219, 0.108199}
    };
    struct_test.particulas.vxyz = {
      {0.0653556, 0.0152707, 0.112494}
    };
    struct_test.particulas.densidad = {0};
    struct_test.particulas.a_c = {
      {0, -9.8, 0}
    };
    struct_test.particulas.bpos = {
      {1, 0, 0}
    };
  }
  TEST(GridTestSuite, TestIncrementoDensidades) {
    Particula particula;
    particula.pxyz = {
      {0.0638389, -0.0495847, 0.000251098},
      {}
    };
    particula.hvxyz = {
      {-0.660175, 15.1248, -19.2416}
    };
    particula.vxyz = {
      {-0.272216, 6.75671, -8.69694}
    };
    particula.densidad = {0};
    particula.a_c = {
      {0, -9.8, 0}
    };
    longitud_y_masa struct_test{204.0f, 4800};
    struct_test.particulas.pxyz = {
      {-0.0123631, -0.0815473, 0.0266473},
  //meter otra partícula
    };
    struct_test.particulas.hvxyz = {
      { 0.0717484, 0.0139219, 0.108199},
      {}
    };
    struct_test.particulas.vxyz = {
      {0.0653556, 0.0152707, 0.112494}
    };
    struct_test.particulas.densidad = {0};
    struct_test.particulas.a_c = {
      {0, -9.8, 0}
    };
    struct_test.particulas.bpos = {
      {1, 0, 0}
    };
    Grid my_cubo(struct_test);
    my_cubo.primeros_calculos();
    my_cubo.choques_entre_particulas();
    // Expect con pxyz de iteración 4 de las trazas repos 4312
    EXPECT_EQ(particula.pxyz[1234][0],  -0.183957);
    EXPECT_EQ(particula.pxyz[1234][1], -0.0652598);
    EXPECT_EQ(particula.pxyz[1234][2], 0.309228);

  }
  TEST(GridTestSuite, TestTransformacionDensidades) {

    // Instancia de Particula

  }
  TEST(GridTestSuite, TestTranferenciaAceleraciones) {

  }

  TEST(GridTestSuite, TestColisionesBorders) {

  }
  TEST(GridTestSuite, TestMovimientoParticulas) {

  }
  TEST(GridTestSuite, TestInteraccionesBordes) {

  }
}