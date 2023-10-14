#include "../sim/progargs.cpp"
#include "../sim/grid.hpp"
#include <span>

int main(int argc, char * argv[]) {
  check_n_arguments(argc);
  std::span const span_args{argv, std::size_t(argc)};
  std::vector<std::string> const arguments{span_args.begin(), span_args.end()};
  std::list<Particula> const particles = argument_validator(arguments);

  double const ppm = ;
  double const masa_particula = ;
  double const longitud_suavizado_h = ;
  Cubo my_cubo;
  my_cubo.set_grid_values();
  my_cubo.creacion_bloques();

  my_cubo.choques_entre_particulas();
  my_cubo.colision_limites();

  file_writer(arguments[3], particles);
  std::cout << "Terminé" << '\n';
  return 0;
}