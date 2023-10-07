#include <cmath>

#include <fstream>
#include <iostream>
#include <list>
#include <span>
#include <string>
#include <vector>


double read_float(std::ifstream & file){
  float number = 0;
  //NOLINTNEXTLINE
  file.read(reinterpret_cast<char*>(&number),4);
  return number;
}

class Particula{
  private:
    double px = 0;
    double py = 0;
    double pz = 0;
    double hvx = 0;
    double hvy = 0;
    double hvz = 0;
    double vx = 0;
    double vy = 0;
    double vz = 0;

  public:
    Particula() = default;
    void printinfo(int counter) const;
    void set_particles_coordinates(std::istream & file);
};


void Particula::printinfo(int counter) const{
  std::cout << "Particula" << counter << '\n';
  std::cout << "px:  " << counter << " " << px <<'\t';
  std::cout << "py:  " << counter << " " << py <<'\t';
  std::cout << "pz:  " << counter << " "<< pz <<'\t';
  std::cout << "hvx:  " << counter << " "<< hvx <<'\t';
  std::cout << "hvy " << counter << " "<< hvx <<'\t';
  std::cout << "hvz " << counter << " "<< hvz <<'\t';
  std::cout << "vx:  " << counter << " "<< vx <<'\t';
  std::cout << "vy " << counter << " "<< vx <<'\t';
  std::cout << "vz " << counter << " "<< vz <<'\n';
}

void Particula::set_particles_coordinates(std::istream & file) {
  px = read_float(*file);
  py = read_float(*file);
  pz = read_float(*file);
  hvx = read_float(*file);
  hvy = read_float(*file);
  hvz = read_float(*file);
  vx = read_float(*file);
  vy = read_float(*file);
  vz = read_float(*file);
}


void argument_validator(std::vector<std::string> arguments){
  // checkjng the validity of the first command (nº of executions)
  const int base = 10;

  if (isdigit(stoi(arguments[1],nullptr,base)) == 1){
    std::cout << "Time steps must be numeric" << '\n';
    exit(-1);
  }
  else if (stoi(arguments[1], nullptr, base) < 0){
    std::cout << "Invalid number of time steps" << '\n';
    exit(-2);
  }

  // for reading the input file
  std::ifstream binary_file(arguments[2],std::ios::binary);
  if (!binary_file){
    std::cout << "Can't Open file" << '\n';
    exit(-3);
  }

  // read the header
  float ppm = 0;
  int n_parameters = 0;

  binary_file.read(reinterpret_cast<char*>(&ppm),4); //NOLINT
  binary_file.read(reinterpret_cast<char*>(&n_parameters),4); //NOLINT

  std::cout << ppm << '\n';
  std::cout << n_parameters << '\n';


  std::list<Particula> list_of_particles;

  int counter = 0;


  while (counter < n_parameters){
    /*
    Particula particle{};
    char buf[4];

######## CREAR UN BUFFER PARA LEER  EL ARCHIVO  METERLO AHÍ EN VEZ DE LEER UNO POR UNO? ########

    ifs.read(buf,sizeof(n_parameters));
    ifs.read(reinterpret_cast<char*>(&particle.px),4);
    ifs.read(reinterpret_cast<char*>(&particle.py ),4);
    ifs.read(reinterpret_cast<char*>(&particle.pz ),4);
    ifs.read(reinterpret_cast<char*>(&particle.hvx ),4);
    ifs.read(reinterpret_cast<char*>(&particle.hvy ),4);
    ifs.read(reinterpret_cast<char*>(&particle.hvz),4);
    ifs.read(reinterpret_cast<char*>(&particle.vx),4);
    ifs.read(reinterpret_cast<char*>(&particle.vy ),4);
    ifs.read(reinterpret_cast<char*>(&particle.vz ),4);

  */


    Particula particula;

    particula.set_particles_coordinates(binary_file);

    list_of_particles.push_back(particula);
    particula.printinfo(counter);

    counter += 1;
  }

}

int main(int argc, char * argv[]){
  if (argc != 4) {
    std::cout << "Invalid number of steps: " << argc << '\n';
    exit(-1);
  }
  std::span const span_args{argv, std::size_t(argc)};
  std::vector<std::string> const arguments{span_args.begin(), span_args.end()};
  argument_validator(arguments);
}
