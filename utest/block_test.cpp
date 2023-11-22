//
// Created by 34638 on 07/10/2023.
//
/*
#include "../sim/vec_block.cpp"
#include "gtest/gtest.h"


namespace {
  TEST(VecBloqueSuite, colision_x_test)
  {
    // Instancia de Vec_Bloque
    Vec_Bloque vec_bloque;
    vec_bloque.lista_particulas = {0};

    // Instancia de Particula
    Particula particula;
    particula.pxyz = {
      {0.35707, 0.434317, 0.0790976}
    };
    particula.hvxyz = {
      { 368.779, 480.998, 57.9082}
    };
    particula.vxyz = {
      {179.918, 239.595, 27.1105}
    };
    particula.densidad={
      321.715
    };
    particula.a_c = {
      {0, -9.8, 0}
    };
    vec_bloque.colision_x(0, particula);
    EXPECT_EQ(particula.a_c[1][0], -42861);
  }
  TEST(VecBloqueSuite, colision_y_test)
  {
    // Instancia de Vec_Bloque
    Vec_Bloque vec_bloque;
    vec_bloque.lista_particulas = {0};

    // Instancia de Particula
    Particula particula;
    particula.pxyz = {
      {0.35707, 0.434317, 0.0790976}
    };
    particula.hvxyz = {
      { 368.779, 480.998, 57.9082}
    };
    particula.vxyz = {
      {179.918, 239.595, 27.1105}
    };
    particula.densidad={
      321.715
    };
    particula.a_c = {
      {0, -9.8, 0}
    };
    vec_bloque.colision_x(0, particula);
    EXPECT_EQ(particula.a_c[1][0], -42861);
  }
  TEST(VecBloqueSuite, colision_z_test)
  {
    // Instancia de Vec_Bloque
    Vec_Bloque vec_bloque;
    vec_bloque.lista_particulas = {0};

    // Instancia de Particula
    Particula particula;
    particula.pxyz = {
      {0.35707, 0.434317, 0.0790976}
    };
    particula.hvxyz = {
      { 368.779, 480.998, 57.9082}
    };
    particula.vxyz = {
      {179.918, 239.595, 27.1105}
    };
    particula.densidad={
      321.715
    };
    particula.a_c = {
      {0, -9.8, 0}
    };
    vec_bloque.colision_x(0, particula);
    EXPECT_EQ(particula.a_c[1][0], -42861);
  }
}
 */