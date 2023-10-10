#include "../sim/progargs.cpp"

#include <span>

int main(int argc, char * argv[]) {
  if (argc != 4) {
    std::cout << "Invalid number of steps: " << argc << '\n';
    exit(-1);
  }
  std::span const span_args{argv, std::size_t(argc)};
  std::vector<std::string> const arguments{span_args.begin(), span_args.end()};
  std::list<Particula> const particles = argument_validator(arguments);
  file_writer(arguments[3], particles);
  std::cout << "Terminé" << '\n';
  return 0;
}
