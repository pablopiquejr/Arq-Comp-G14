//
// Created by sergio on 7/10/23.
//

#include "progargs.hpp"

float ppm        = 0;
int n_parameters = 0;


void check_n_arguments(int argc) {
  if (argc != 4) {
    std::cout << "Invalid number of steps: " << argc << '\n';
    exit(-1);
  }
}
void validate_number(std::string const & n_iterations) {
  int const base = 10;
  if (isdigit(stoi(n_iterations, nullptr, base)) == 1) {
    std::cout << "Time steps must be numeric" << '\n';
    exit(-1);
  } else if (stoi(n_iterations, nullptr, base) < 0) {
    std::cout << "Invalid number of time steps" << '\n';
    exit(-2);
  }
}

std::list<Particula> file_reader(std::string const & file_name) {
  std::ifstream binary_file(file_name, std::ios::binary);
  if (!binary_file) {
    std::cout << "Can't Open input file" << '\n';
    exit(-3);
  }
  // read the header
  binary_file.read(reinterpret_cast<char *>(&ppm), 4);           // NOLINT
  binary_file.read(reinterpret_cast<char *>(&n_parameters), 4);  // NOLINT
  if (n_parameters<=0){
      exit(-5);
  }
  std::list<Particula> list_of_particles;
  double counter = 0;
  while (counter < n_parameters) {
    Particula particula;
    particula.set_particles_data(binary_file, counter);
    list_of_particles.push_back(particula);
    // particula.printinfo(counter);
    counter += 1;
  }
  if (counter<=0){
      exit(-5);
  }
  return list_of_particles;
}

std::list<Particula> argument_validator(std::vector<std::string> arguments) {
  // checking the validity of the first command (nº of executions)
  validate_number(arguments[1]);

  // validate and read input file
  return file_reader(arguments[2]);
}

void file_writer(std::string const & name, std::list<Particula> const & list_of_particles) {
  std::ofstream output{name, std::ios::binary};
  if (!output) {
    std::cout << "Can't Open output file " << '\n';
    exit(-4);
  }
  for (auto const & elem : list_of_particles) {
    std::string const parameters = elem.particle_write();
    output.write(reinterpret_cast<char const *>(&parameters), 36);  // NOLINT
  }
}

void declaración_m_h() {
  m_particula = p_densidad / std::pow(ppm, 3.0);
  h_logitud_suavizado = r_radio / ppm;
}



