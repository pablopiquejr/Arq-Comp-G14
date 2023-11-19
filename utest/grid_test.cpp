#include "../sim/vec_grid.cpp"
#include "../sim/progargs.cpp"
#include "gtest/gtest.h"

namespace {

  TEST(GridTestSuite, TestReposicionamientoParticulas) {
    int const index_particle           = 1234;
    std::vector<double> const position = {0.50000, 0.50000, 0.50000};

    // Instancia de Particula
    Particula particula;
    particula.pxyz = {
      {0.35707, 0.434317, 0.0790976}
    };
    particula.hvxyz = {
      {368.779, 480.998, 57.9082}
    };
    particula.vxyz = {
      {179.918, 239.595, 27.1105}
    };
    particula.densidad = {321.715};
    particula.a_c      = {
      {0, -9.8, 0}
    };
    longitud_y_masa mi_struct;
    Grid my_cubo(mi_struct);
    my_cubo.primeros_calculos();
    my_cubo.reposicionar_particula(particula, index_particle, position);
    EXPECT_EQ(particula.pxyz[0][0], -0.50000);
  }
}