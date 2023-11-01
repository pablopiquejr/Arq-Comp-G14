//
// Created by sergio on 7/10/23.
//

#include "progargs.hpp"

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

struct longitud_y_masa file_reader(std::string const & file_name) {
  std::ifstream binary_file(file_name, std::ios::binary);
  if (!binary_file) {
    std::cout << "Can't Open input file" << '\n';
    exit(-3);
  }
  // read the header
  float ppm        = 0;
  int n_parameters = 0;
  binary_file.read(reinterpret_cast<char *>(&ppm), 4);           // NOLINT
  binary_file.read(reinterpret_cast<char *>(&n_parameters), 4);  // NOLINT
  longitud_y_masa l_m{ppm, n_parameters};
  if (n_parameters <= 0) { exit(-m_num_5); }
  double counter = 0;
  while (counter < n_parameters) {
    Particula particula;
    particula.set_particles_data(binary_file, counter);
    l_m.list_of_particles.push_back(particula);
    // particula.printinfo(counter);
    counter += 1;
  }
  if (counter <= 0) { exit(-m_num_5); }
  return l_m;
}

struct longitud_y_masa argument_validator(std::vector<std::string> arguments) {
  // checking the validity of the first command (nº of executions)
  validate_number(arguments[1]);

  // validate and read input file
  return file_reader(arguments[2]);
}

void file_writer(std::string const & name, longitud_y_masa mis_datos) {
  std::ofstream output{name, std::ios::binary};
  if (!output) {
    std::cout << "Can't Open output file " << '\n';
    exit(-4);
  }
  // Escribir la cabecera
  output.write(reinterpret_cast<char *>(&mis_datos.ppm), 4);           // NOLINT
  output.write(reinterpret_cast<char *>(&mis_datos.n_particulas), 4);  // NOLINT
  // Escribir los datos de todas las particulas
  std::vector<float> my_data;
  for (Particula const & particula : mis_datos.list_of_particles) {
    my_data = particula.particle_write();
    for (float elemento : my_data) {
      output.write(reinterpret_cast<char *>(&elemento), 4);  // NOLINT
    }
    particula.printinfo();
  }
}

/*
void print_all_starting_data(){
  continue;
}

 */
