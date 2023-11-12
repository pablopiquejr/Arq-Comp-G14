//
// Created by 34638 on 07/10/2023.
//

#include "../sim/vec_block.cpp"
#include "gtest/gtest.h"
#include "../sim/vec_block.hpp"

// https://google.github.io/googletest/reference/assertions.html

namespace
{
  TEST(BlockSuite,colision_x_baja_test)
  {
    // Simula una lista de partículas (ajusta según tu implementación).
    // Debes inicializarla con los valores necesarios para la prueba.
    // Por ejemplo:
    // std::vector<Particula> lista_particulas = { ... };
  }
  TEST(BlockSuite, colision_y_baja_test)
  {
    // Simula una lista de partículas (ajusta según tu implementación).
    // Debes inicializarla con los valores necesarios para la prueba.
    // Por ejemplo:
    // std::vector<Particula> lista_particulas = { ... };
  }

  TEST(BlockSuite, ncolision_z_baja_test)
  {
    // Simula una lista de partículas (ajusta según tu implementación).
    // Debes inicializarla con los valores necesarios para la prueba.
    // Por ejemplo:
    // std::vector<Particula> lista_particulas = { ... };
  }

  TEST(BlockSuite,colision_x_alta_test)
  {
    // Simula una lista de partículas (ajusta según tu implementación).
    // Debes inicializarla con los valores necesarios para la prueba.
    // Por ejemplo:
    // std::vector<Particula> lista_particulas = { ... };
  }
  TEST(BlockSuite, colision_y_alta_test)
  {
    // Simula una lista de partículas (ajusta según tu implementación).
    // Debes inicializarla con los valores necesarios para la prueba.
    // Por ejemplo:
    // std::vector<Particula> lista_particulas = { ... };
  }

  TEST(BlockSuite, ncolision_z_alta_test)
  {
    // Simula una lista de partículas (ajusta según tu implementación).
    // Debes inicializarla con los valores necesarios para la prueba.
    // Por ejemplo:
    // std::vector<Particula> lista_particulas = { ... };

}

TEST(VecBloqueSuite, colision_x_test)
{
    // Instancia de Vec_Bloque
    Vec_Bloque vec_bloque;
    vec_bloque.lista_particulas = {0, 1};

    // Instancia de Particula
    Particula particula;
    particula.pxyz = {{0.05, 0.5, 0.5}, {0.95, 0.5, 0.5}};
    particula.hvxyz = {{1, 0, 0}, {-1, 0, 0}};
    particula.vxyz = {{0, 0, 0}, {0, 0, 0}};
    particula.a_c = {{0, 0, 0}, {0, 0, 0}};

    // Llamada a la función y verificación de los resultados
    vec_bloque.colision_x(0, particula);
    EXPECT_EQ(particula.a_c[0][0], 0.0);
    EXPECT_EQ(particula.a_c[1][0], 0.0);

    // Reinicialización de la particula y nueva llamada a la función
    particula.pxyz = {{0.05, 0.5, 0.5}, {0.95, 0.5, 0.5}};
    particula.hvxyz = {{1, 0, 0}, {-1, 0, 0}};
    particula.vxyz = {{0, 0, 0}, {0, 0, 0}};
    particula.a_c = {{0, 0, 0}, {0, 0, 0}};
    vec_bloque.colision_x(1, particula);

    // Verificación de los resultados
    EXPECT_EQ(particula.a_c[0][0], -0.1);
    EXPECT_EQ(particula.a_c[1][0], 0.1);
}
}