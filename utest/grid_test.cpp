#include "../sim/vec_grid.cpp"
#include "../sim/progargs.cpp"
#include "gtest/gtest.h"

namespace {

  TEST(GridTestSuite, TestReposicionamientoParticulas) {
    int const index_particle           = 1234;
    std::vector<double> const position = {1, 0, 9};

    // Instancia de Particula
    Particula particula;
    particula.pxyz = {
      {-0.0123631, -0.0815473, 0.0266473}
    };
    particula.hvxyz = {
      { 0.0717484, 0.0139219, 0.108199}
    };
    particula.vxyz = {
      {0.0653556, 0.0152707, 0.112494}
    };
    particula.densidad = {0};
    particula.a_c = {
      {0, -9.8, 0}
    };
    longitud_y_masa struct_test{204.0f, 4800};
    Grid my_cubo(struct_test);
    my_cubo.primeros_calculos();
    my_cubo.reposicionar_particula(particula, index_particle, position);
    my_cubo.check_if_repos();
    EXPECT_EQ(particula.pxyz[1234][0], -0.040281);
    EXPECT_EQ(particula.pxyz[1234][1], -0.0650672);
    EXPECT_EQ(particula.pxyz[1234][2], 0.00368461);
  }

  TEST(GridTestSuite, TestIncrementoAceleracion){
    int const index1 = 4321;
    int const index2 = 5678;
    Particula particula;
    particula.pxyz = {
      {-0.040281, -0.0650672, 0.00368461}
    };
    particula.hvxyz = {
      { -31.6856, 21.8196, -29.2818}
    };
    particula.vxyz = {
      {-13.6254, 7.78405, -10.9486}

    };
    particula.densidad = {0};
    particula.a_c = {
      {0, -9.8, 0}
    };
    longitud_y_masa struct_test{204.0f, 4800};
    Grid my_cubo(struct_test);
    my_cubo.primeros_calculos();
    my_cubo.incremento_aceleracion(particula, index1, index2, 0.1);
    EXPECT_EQ(particula.a_c[1234][0],186.254);
    EXPECT_EQ(particula.a_c[1234][1], 58.2616);
    EXPECT_EQ(particula.a_c[1234][2], 43.118);
  }

  TEST(GridTestSuite, TestIncrementoDensidades){
    int const index1 = 4321;
    int const index2 = 5678;
    Particula particula;
    particula.pxyz = {
      {-0.040281, -0.0650672, 0.00368461}
    };
    particula.hvxyz = {
      { -31.6856, 21.8196, -29.2818}
    };
    particula.vxyz = {
      {-13.6254, 7.78405, -10.9486}

    };
    particula.densidad = {0};
    particula.a_c = {
      {0, -9.8, 0}
    };
    longitud_y_masa struct_test{204.0f, 4800};
    Grid my_cubo(struct_test);
    my_cubo.primeros_calculos();
    my_cubo.incremento_aceleracion(particula, index1, index2, 0.1);
    EXPECT_EQ(particula.a_c[1234][0],186.254);
    EXPECT_EQ(particula.a_c[1234][1], 58.2616);
    EXPECT_EQ(particula.a_c[1234][2], 43.118);
  }
  TEST(GridTestSuite, TestTranformacionDensidades){

  }
  TEST(GridTestSuite, TestTransferenciaAceleracion

  }
   TEST(GridTestSuite, TestTransferenciaAceleraciones){

  }
   TEST(GridTestSuite, TestColisionesBordes) {

}
   TEST(GridTestSuite, TestMovimientoParticulas) {

   }
   TEST(GridTestSuite, TestInteracciónBordes) {

   }
}