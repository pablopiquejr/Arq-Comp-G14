//
// Created by 34638 on 12/11/2023.
//
#include "../sim/vec_grid.cpp"
#include "../sim/progargs.cpp"
#include "../sim/vec_block.cpp"

#include "gtest/gtest.h"

// https://google.github.io/googletest/reference/assertions.html

namespace
{
  TEST(FunctionalTestSuite, stimated_time_test)
  {
    //Empezamos el cronómetro
    auto start_time = std::chrono::high_resolution_clock::now();

    //Ejecutamos el proyecto con el archivo large
    const char* command = "g++ ../fluid/fluid.cpp -o fluid";
    const char* command1 = "./fluid";
    EXPECT_EQ(system(command),0);
    EXPECT_EQ(system(command1),0);

    //Acabamos de contar
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calcular tiempo de ejecucion
    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // Verificar si es menos que el tiempo mejorable y el óptimo
    EXPECT_GE(elapsed_time.count(), 45 * 1000000);
    EXPECT_LE(elapsed_time.count(), 55 * 1000000);

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