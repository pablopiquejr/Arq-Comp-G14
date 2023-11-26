//
// Created by sergio on 7/10/23.
//

#include "progargs.hpp"

// Comprobar que el numero de argumentos es el esperado
void progargs::check_n_arguments(int argc) {
  if (argc != 4) {
    std::cerr << "Invalid number of steps: " << argc << '\n';
    exit(-1);
  }
}

// Comprobar que el numero de iteracciones es un integer.
void progargs::validate_number(std::string const & n_iterations) {
  int const base = 10;
  try {
    stoi(n_iterations, nullptr, base);
  } catch (std::invalid_argument &) {
    std::cerr << "Time steps must be numeric" << '\n';
    exit(-1);
  }
  if (stoi(n_iterations, nullptr, base) < 0) {
    std::cerr << "Invalid number of time steps" << '\n';
    exit(-2);
  }
}

// Leer de tres en tres los datos de las particulas
std::array<double, 3> progargs::read_data(std::ifstream & file) {
  std::array<double, 3> sol = {};
  for (int i = 0; i < 3; i++) {
    float number = 0;
    // NOLINTNEXTLINE
    file.read(reinterpret_cast<char *>(&number), 4);
    sol.at(i) = number;
  }
  return sol;
}

// Escribir, en este caso se podŕia optimizar con array, pero no habría mucha mejora.
std::vector<float> progargs::write_data(std::array<double, 3> pxyz, std::array<double, 3> hvxyz,
                                        std::array<double, 3> vxyz) {
  std::vector<float> data(pxyz.begin(), pxyz.end());

  std::vector<float> h_v(hvxyz.begin(), hvxyz.end());

  std::vector<float> v_aux(vxyz.begin(), vxyz.end());

  data.insert(data.end(), h_v.begin(), h_v.end());
  data.insert(data.end(), v_aux.begin(), v_aux.end());
  return data;
}

// Función que lee el archivo, genera y completa el setter que posteriormente vamos a usar para
// nuestras operaciones
struct setter progargs::file_reader(std::string const & file_name) {
  // Abrir el archivo y comprobar que no de error
  std::ifstream binary_file(file_name, std::ios::binary);
  if (!binary_file) {
    std::cerr << "Can't Open input file" << '\n';
    exit(-3);
  }
  // Leer la cabecera
  float ppm        = 0;
  int n_parameters = 0;
  binary_file.read(reinterpret_cast<char *>(&ppm), 4);           // NOLINT
  binary_file.read(reinterpret_cast<char *>(&n_parameters), 4);  // NOLINT
  // Inicializar nuestro setter
  setter l_m{ppm, n_parameters};
  if (n_parameters <= 0) { exit(-m_num_5); }
  long counter = 0;
  while (counter < n_parameters) {
    // Leer los tres parametros de cada particula
    l_m.particulas.pxyz[counter]   = read_data(binary_file);
    l_m.particulas.hvxyz[counter]  = read_data(binary_file);
    l_m.particulas.vxyz[counter]   = read_data(binary_file);
    counter                       += 1;
  }
  if (counter <= 0) { exit(-m_num_5); }
  return l_m;
}

struct setter progargs::argument_validator(std::vector<std::string> arguments) {
  // Comprobar que las iteracciones sean un numero
  validate_number(arguments[1]);

  // validar el archivo de lectura
  return file_reader(arguments[2]);
}

void progargs::file_writer(std::string const & name, setter mis_datos) {
  // Generar el archivo donde vas a escribir
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
    my_data = write_data(mis_datos.particulas.pxyz[i], mis_datos.particulas.hvxyz[i],
                         mis_datos.particulas.vxyz[i]);
    for (float elemento : my_data) {
      output.write(reinterpret_cast<char *>(&elemento), 4);  // NOLINT
    }
  }
}