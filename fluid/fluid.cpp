#include "../sim/grid.hpp"
#include "../sim/progargs.cpp"

#include <span>

int main(int argc, char * argv[]) {
  check_n_arguments(argc);
  std::span const span_args{argv, std::size_t(argc)};
  std::vector<std::string> const arguments{span_args.begin(), span_args.end()};
  longitud_y_masa mi_struct = argument_validator(arguments);
  int const n_interacciones       =  1;//stoi(arguments[1]);
  Cubo my_cubo(mi_struct);
  for (int i = 0; i < n_interacciones; i++) {
    my_cubo.set_grid_values();
    my_cubo.creacion_bloques();

    my_cubo.choques_entre_particulas();
    my_cubo.colision_limites();

    std::cout << "Terminé" << '\n';
  }
  file_writer(arguments[3], my_cubo.l_m);
  return 0;
}