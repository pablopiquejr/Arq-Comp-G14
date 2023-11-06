
#include "../sim/progargs.cpp"


#include <span>

/*
#include "../sim/grid.hpp"

int main(int argc, char * argv[]) {
  check_n_arguments(argc);
  std::span const span_args{argv, std::size_t(argc)};
  std::vector<std::string> const arguments{span_args.begin(), span_args.end()};
  longitud_y_masa mi_struct = argument_validator(arguments);

  int const n_interacciones       =  1;//stoi(arguments[1]);
  Cubo my_cubo(mi_struct);
  my_cubo.set_grid_values();
  my_cubo.creacion_bloques();


  //////////////////////////////////////////////////////////
  // HAY QUE CAMBIAR EL GRID A VECGRID ANTES DE CORRERLO////
  //////////////////////////////////////////////////////////


  for (int i = 0; i < n_interacciones; i++) {
      //va a hacer una iteracion extra de repos
      my_cubo.repos_particulas();
      my_cubo.choques_entre_particulas();
      //std::cout << "Colisiones" << "\n";
      //my_cubo.colision_limites();
      my_cubo.procesamiento_colisiones();
  }
  longitud_y_masa final = my_cubo.actualizar_lista();
  file_writer(arguments[3], final);
  std::cout << "Terminé" << '\n';
  return 0;
}
*/


#include "../sim/v2_optimizaciones/vec_grid.hpp"

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
    //my_cubo.colision_limites();
    my_cubo.write_report(i+1);
  }
  file_writer(arguments[3], my_cubo.l_m);
  std::cout << "Terminé" << '\n';
  return 0;
}
