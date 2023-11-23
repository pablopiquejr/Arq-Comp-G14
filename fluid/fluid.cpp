
#include "../sim/Grid.hpp"
#include "../sim/progargs.cpp"

#include <span>

int main(int argc, char * argv[]) {
  progargs const inicio;
  // Comprobar la validez de los argumentos
  inicio.check_n_arguments(argc);
  // Usar span y vector para pasar los inputs como parametros
  std::span const span_args{argv, std::size_t(argc)};
  std::vector<std::string> const arguments{span_args.begin(), span_args.end()};
  setter mi_struct = inicio.argument_validator(arguments);

  int const n_interacciones = stoi(arguments[1]);
  // Generar nuestra malla
  Grid my_cubo(mi_struct);
  // Dar los valores iniciales necesarios de la malla
  my_cubo.primeros_calculos();

  for (int i = 0; i < n_interacciones; i++) {
    // Hacer todos los pasos el numero de iteracciones necesarias
    my_cubo.check_if_repos();
    my_cubo.choques_entre_particulas();
    my_cubo.procesamiento_colisiones();
  }
  // Escribir en el archivo de salida
  inicio.file_writer(arguments[3], my_cubo.l_m);
  return 0;
}