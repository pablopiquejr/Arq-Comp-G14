
#include "../sim/progargs.cpp"
#include "sim/vec_grid.hpp"

#include <span>

int main(int argc, char * argv[]) {
  check_n_arguments(argc);
  std::span const span_args{argv, std::size_t(argc)};
  std::vector<std::string> const arguments{span_args.begin(), span_args.end()};
  longitud_y_masa mi_struct = argument_validator(arguments);

  int const n_interacciones       =  stoi(arguments[1]);
  Grid my_cubo(mi_struct);
  my_cubo.primeros_calculos();

  for (int i = 0; i < n_interacciones; i++) {
    my_cubo.check_if_repos();
    my_cubo.choques_entre_particulas();
    my_cubo.procesamiento_colisiones();
    //my_cubo.write_report(i+1);
  }
  file_writer(arguments[3], my_cubo.l_m);
  return 0;
}