//
// Created by 34638 on 12/11/2023.
//
#include "../sim/vec_grid.cpp"
#include "../sim/progargs.cpp"
#include "../sim/vec_block.cpp"

#include "gtest/gtest.h"
#include "product.hpp"
#include "product.cpp"

#include <fstream>

// https://google.github.io/googletest/reference/assertions.html

namespace
{
  /*
  TEST(FunctionalTestSuite, stimated_time_test)
  {
    //Empezamos el cronómetro
    auto start_time = std::chrono::high_resolution_clock::now();

    //Ejecutamos el proyecto con el archivo large
    const char* command = "../cmake-build-debug/fluid/fluid 5 ../large.fld ../../output.fld";
    EXPECT_EQ(system(command),0);

    //Acabamos de contar
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calcular tiempo de ejecucion
    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // Verificar si es menos que el tiempo mejorable y el óptimo
    EXPECT_GE(elapsed_time.count(), 45 * 1000000);
    EXPECT_LE(elapsed_time.count(), 55 * 1000000);
  }
  */

  TEST(FunctionalTestSuite, output_file_format_test)
  {
    // Abrir el archivo de salida
    std::ifstream output_file("../output.fld");
    std::string file_extension;

    // Obtener la extensión del archivo
    if (output_file.is_open())
    {
      std::string line;
      while (getline(output_file, line))
      {
        if (line.find("FORMAT") != std::string::npos)
        {
          file_extension = line.substr(line.find_last_of(".") + 1);
          break;
        }
      }
      output_file.close();
    }

    // Verificar si la extensión es ".fld"
    EXPECT_EQ(file_extension, "fld");
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

TEST(FunctionalTestSuite, input_file_format_test)
{
  // Abrir el archivo de entrada
  std::ifstream input_file("../large.fld");
  std::string file_extension;

  // Obtener la extensión del archivo
  if (input_file.is_open())
  {
    std::string line;
    while (getline(input_file, line))
    {
      if (line.find("FORMAT") != std::string::npos)
      {
        file_extension = line.substr(line.find_last_of(".") + 1);
        break;
      }
    }
    input_file.close();
  }

  // Verificar si la extensión es ".fld"
  EXPECT_EQ(file_extension, "fld");
}
