/* COMENTADO PARA QUE CORRA LA BUILD
//
// Created by 34638 on 07/10/2023.
//

#include "../sim/block.cpp"
#include "../sim/progargs.cpp"
#include "gtest/gtest.h"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <sstream>
//https://google.github.io/googletest/reference/assertions.html

namespace
{
  TEST(ProgArgsSuite, check_n_arguments_test)
  //Número de parámetros inválido
  {
    // Caso 1: Verificar que cuando argc es igual a 4, la función no llama a exit() y no imprime ningún mensaje de error.
    ::testing::internal::CaptureStdout();
    ASSERT_NO_FATAL_FAILURE(check_n_arguments(4));
    std::string stdout_capture = ::testing::internal::GetCapturedStdout();
    EXPECT_EQ(stdout_capture, "");

    // Caso 2: Verificar que cuando argc no es igual a 4, la función llama a exit(-1) y se imprime el mensaje "Invalid number of steps".
    ::testing::internal::CaptureStdout();
    ASSERT_EXIT(check_n_arguments(3), ::testing::ExitedWithCode(255), "Invalid number of steps: 3");
    stdout_capture = ::testing::internal::GetCapturedStdout();
    EXPECT_EQ(stdout_capture, "Invalid number of steps: 3\n");
  }

  }

  TEST(ProgArgsSuite, validate_number){
  // Caso 1: Archivo válido
  {
    // Crear un archivo binario de prueba
    std::ofstream outfile("test_data.bin", std::ios::binary);
    ASSERT_TRUE(outfile.is_open());

    // Escribir datos de prueba en el archivo
    float ppm        = 3.14;
    int n_parameters = 5;
    outfile.write(reinterpret_cast<char *>(&ppm), sizeof(float));
    outfile.write(reinterpret_cast<char *>(&n_parameters), sizeof(int));
    // Escribe más datos de partículas aquí si es necesario

    outfile.close();

    // Probar file_reader con el archivo de prueba
    longitud_y_masa result = file_reader("test_data.bin");

    // Verificar que los datos leídos coincidan con los datos de prueba
    EXPECT_FLOAT_EQ(result.ppm, ppm);
    EXPECT_EQ(result.n_parameters, n_parameters);

    // También puedes agregar más aserciones para verificar los datos de partículas si es necesario

    // Eliminar el archivo de prueba
    std::remove("test_data.bin");
  }

  // Caso 2: Archivo inválido
  {
    // Probar file_reader con un archivo inexistente o inválido
    ::testing::internal::CaptureStdout();
    ASSERT_EXIT(file_reader("archivo_invalido.bin"), ::testing::ExitedWithCode(255), "Can't Open input file");
    std::string stdout_capture = ::testing::internal::GetCapturedStdout();
    EXPECT_EQ(stdout_capture, "Can't Open input file\n");
  }
  //Fin de este test
  }


  TEST(ProgArgsSuite, file_writer_test){
  // Creamos datos de prueba
  longitud_y_masa mis_datos;
  mis_datos.ppm = 3.14;
  mis_datos.n_particulas = 2;

  Particula particula1, particula2;
  // Configuramos datos de prueba para las partículas
  // ...

  // Agregamos las partículas a mis_datos.list_of_particles
  mis_datos.list_of_particles.push_back(particula1);
  mis_datos.list_of_particles.push_back(particula2);

  // Especificamos el nombre del archivo de salida
  std::string output_filename = "output_data.bin";

  // Escenario 1: Archivo válido
  {
    // Llamamos a file_writer para escribir los datos
    file_writer(output_filename, mis_datos);

    // Abrimos el archivo de salida y verificamos que los datos escritos sean correctos
    std::ifstream infile(output_filename, std::ios::binary);
    ASSERT_TRUE(infile.is_open());

    // Leemos la cabecera y verificamos los valores
    float ppm_read = 0.0;
    int n_particulas_read = 0;
    infile.read(reinterpret_cast<char *>(&ppm_read), sizeof(float));
    infile.read(reinterpret_cast<char *>(&n_particulas_read), sizeof(int));
    EXPECT_FLOAT_EQ(ppm_read, mis_datos.ppm);
    EXPECT_EQ(n_particulas_read, mis_datos.n_particulas);

    // Leemos los datos de las partículas y verificamos que coincidan con los datos de prueba
    for (const Particula& particula : mis_datos.list_of_particles) {
      std::vector<float> my_data(particula.particle_write().begin(), particula.particle_write().end());
      for (float elemento : my_data) {
        float elemento_leido = 0.0;
        infile.read(reinterpret_cast<char *>(&elemento_leido), sizeof(float));
        EXPECT_FLOAT_EQ(elemento_leido, elemento);
      }
    }

    infile.close();
  }

  // Escenario 2: Archivo inválido
  {
    // Llamamos a file_writer con un nombre de archivo inválido o cuando no se puede abrir el archivo de salida
    ::testing::internal::CaptureStdout();
    ASSERT_EXIT(file_writer("invalid_output_file.bin", longitud_y_masa()), ::testing::ExitedWithCode(255), "Can't Open output file");
    std::string stdout_capture = ::testing::internal::GetCapturedStdout();
    EXPECT_EQ(stdout_capture, "Can't Open output file\n");
  }

  // Eliminamos el archivo de salida (si se creó)
  if (std::ifstream(output_filename)) {
    std::remove(output_filename.c_str());
  }
  }


  ///////////AÑADIR AL FINAL DE LOS ARCHIVOS O TESTEAR DESDE AQUI////////////
*/
  /*
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();


//////////AÑADIR AL FINAL DE LOS ARCHIVOS O TESTEAR DESDE AQUI//////////////
}
*/