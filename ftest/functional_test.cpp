//
// Created by 34638 on 12/11/2023.
//
#include "../sim/Block.cpp"
#include "../sim/Grid.cpp"
#include "../sim/progargs.cpp"
#include "filesystem"

#include "gtest/gtest.h"

// https://google.github.io/googletest/reference/assertions.html

namespace {

  TEST(FunctionalTestSuite, estimated_time_test) {

    // Empezamos el cronómetro
    auto start_time = std::chrono::high_resolution_clock::now();

    // Ejecutamos el proyecto con el archivo large
    const char* command =
        "cd ../../cmake-build-release/ && fluid/fluid 1000 ../large.fld output.fld";
    int return_code = std::system(command);

    // Verificar si el comando se ejecutó correctamente (código de retorno igual a 0)
    EXPECT_EQ(return_code, 0);

    // Acabamos de contar
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calcular tiempo de ejecucion
    auto elapsed_time =
        std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // Verificar si es menos que el tiempo mejorable y el óptimo
    EXPECT_GE(elapsed_time.count(), 45 * 1000000);
    EXPECT_LE(elapsed_time.count(), 55 * 1000000);
  }

  TEST(OutputFileTestSuite, VerifyFileContent) {
    // Nombre del archivo
    std::string filename = "/home/kikealcocerdz/CLionProjects/Arq-Comp-G14/output.fld";

    // Abrir el archivo
    std::ifstream file(filename);

    // Verificar si el archivo se abrió correctamente
    ASSERT_TRUE(file.is_open()) << "No se pudo abrir el archivo: " << filename;

    // Cerrar el archivo
    file.close();
  }

  TEST(InputLargeFileTestSuite, VerifyFileContent) {
    // Nombre del archivo
    std::string filename = "/home/kikealcocerdz/CLionProjects/Arq-Comp-G14/large.fld";

    // Verificar la extensión del archivo
    std::filesystem::path filePath(filename);
    std::string extension = filePath.extension().string();
    ASSERT_EQ(extension, ".fld") << "La extensión del archivo no es .fld";

    // Abrir el archivo
    std::ifstream file(filename);

    // Verificar si el archivo se abrió correctamente
    ASSERT_TRUE(file.is_open()) << "No se pudo abrir el archivo: " << filename;

    // Cerrar el archivo
    file.close();
  }

  TEST(InputSmallFileTestSuite, VerifyFileContent) {
    // Nombre del archivo
    std::string filename = "/home/kikealcocerdz/CLionProjects/Arq-Comp-G14/small.fld";

    // Verificar la extensión del archivo
    std::filesystem::path filePath(filename);
    std::string extension = filePath.extension().string();
    ASSERT_EQ(extension, ".fld") << "La extensión del archivo no es .fld";

    // Abrir el archivo
    std::ifstream file(filename);

    // Verificar si el archivo se abrió correctamente
    ASSERT_TRUE(file.is_open()) << "No se pudo abrir el archivo: " << filename;

    // Cerrar el archivo
    file.close();
  }

}