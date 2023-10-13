#include "../sim/progargs.cpp"
#include "../sim/grid.hpp"
#include "../sim/particle.hpp"
#include <span>

int main(int argc, char * argv[]) {
  check_n_arguments(argc);
  std::span const span_args{argv, std::size_t(argc)};
  std::vector<std::string> const arguments{span_args.begin(), span_args.end()};
  std::list<Particula> const particles = argument_validator(arguments);
  declaracion_tamaño_bloque();
  declaración_m_h();
  creacion_bloques();


  file_writer(arguments[3], particles);
  std::cout << "Terminé" << '\n';
  return 0;
}
void asignacion_inicial(){
  for (int i; i < 10; i++){
    continue;
  }

};