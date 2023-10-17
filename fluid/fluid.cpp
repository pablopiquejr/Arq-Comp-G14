#include "../sim/h_y_m_struct.hpp"
#include "../sim/progargs.cpp"
#include <span>


int main(int argc, char * argv[]) {
  check_n_arguments(argc);
  std::span const span_args{argv, std::size_t(argc)};
  std::vector<std::string> const arguments{span_args.begin(), span_args.end()};
  longitud_y_masa mi_struct = argument_validator(arguments);

  /*
  double const ppm = ;
  double const masa_particula = ;
  double const longitud_suavizado_h = ;

  Cubo my_cubo;
  my_cubo.set_grid_values();
  my_cubo.creacion_bloques();

  my_cubo.choques_entre_particulas();
  my_cubo.colision_limites();
  */
  file_writer(arguments[3], mi_struct);
  std::cout << "Terminé" << '\n';
  return 0;
}