//
// Created by sergio on 7/10/23.
//

#include "progargs.hpp"

std::vector<double> read_data(std::ifstream & file) {
  std::vector<double> sol;
  for (int i =0; i < 3; i++) {
    float number = 0;
    // NOLINTNEXTLINE
    file.read(reinterpret_cast<char *>(&number), 4);
    sol.push_back(number);
  }
  return sol;
}

std::vector<float>  write_data(std::vector<double> pxyz,

                std::vector<double>hvxyz,
                std::vector<double>vxyz){
  std::vector<float> data(pxyz.begin(),pxyz.end());

  std::vector<float> h_v(hvxyz.begin(),hvxyz.end());

  std::vector<float> v_aux(vxyz.begin(),vxyz.end());

  data.insert(data.end(), h_v.begin(),h_v.end());
  data.insert(data.end(), v_aux.begin(),v_aux.end());
  return data;
}

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
  long counter = 0;
  while (counter < n_parameters) {
    l_m.particulas.pxyz.push_back(read_data(binary_file));
    l_m.particulas.hvxyz.push_back(read_data(binary_file));
    l_m.particulas.vxyz.push_back(read_data(binary_file));
    l_m.particulas.a_c.push_back({0,gravedad,0});
    l_m.particulas.densidad.push_back(0);
    l_m.particulas.bpos.push_back({0,0,0});
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
  for (int i = 0; i < mis_datos.n_particulas; i++) {
    my_data = write_data(mis_datos.particulas.pxyz[i],mis_datos.particulas.hvxyz[i],mis_datos.particulas.vxyz[i]);
    for (float elemento : my_data) {
      output.write(reinterpret_cast<char *>(&elemento), 4);  // NOLINT
    }
  }
}

