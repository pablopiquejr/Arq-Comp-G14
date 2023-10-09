#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <span>
#include <string>
#include <vector>

double read_float(std::ifstream & file) {
  float number = 0;
  // NOLINTNEXTLINE
  file.read(reinterpret_cast<char *>(&number), 4);
  return number;
}

class Particula {
  private:
    double px  = 0;
    double py  = 0;
    double pz  = 0;
    double hvx = 0;
    double hvy = 0;
    double hvz = 0;
    double vx  = 0;
    double vy  = 0;
    double vz  = 0;

  public:
    Particula() = default;
    void printinfo(int counter) const;
    void set_particles_coordinates(std::ifstream & file);
    [[nodiscard]] std::string particle_write() const;
};

std::string Particula::particle_write() const {
  std::string parameters;
  parameters += std::to_string(px);
  parameters += std::to_string(py);
  parameters += std::to_string(pz);
  parameters += std::to_string(hvx);
  parameters += std::to_string(hvy);
  parameters += std::to_string(hvz);
  parameters += std::to_string(vx);
  parameters += std::to_string(vy);
  parameters += std::to_string(vz);
  return parameters;
}

void Particula::printinfo(int counter) const {
  std::cout << "Particula" << counter << '\n';
  std::cout << "px:  " << px << '\t';
  std::cout << "py:  " << py << '\t';
  std::cout << "pz:  " << pz << '\t';
  std::cout << "hvx:  " << hvx << '\t';
  std::cout << "hvy " << hvy << '\t';
  std::cout << "hvz " << hvz << '\t';
  std::cout << "vx:  " << vx << '\t';
  std::cout << "vy " << vy << '\t';
  std::cout << "vz " << vz << '\n';
}

void Particula::set_particles_coordinates(std::ifstream & file) {
  px  = read_float(file);
  py  = read_float(file);
  pz  = read_float(file);
  hvx = read_float(file);
  hvy = read_float(file);
  hvz = read_float(file);
  vx  = read_float(file);
  vy  = read_float(file);
  vz  = read_float(file);
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
  float ppm        = 0;
  int n_parameters = 0;

  binary_file.read(reinterpret_cast<char *>(&ppm), 4);           // NOLINT
  binary_file.read(reinterpret_cast<char *>(&n_parameters), 4);  // NOLINT

  std::list<Particula> list_of_particles;
  int counter = 0;
  while (counter < n_parameters) {
    Particula particula;
    particula.set_particles_coordinates(binary_file);
    list_of_particles.push_back(particula);
    // particula.printinfo(counter);
    counter += 1;
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
