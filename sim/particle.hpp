//
// Created by sergio on 5/10/23.
//

#include <iostream>
#include "constants.hpp"

class Particula{
  public:
    double identifier = 0;
    double px = 0;
    double py = 0;
    double pz = 0;
    double hvx = 0;
    double hvy = 0;
    double hvz = 0;
    double vx = 0;
    double vy = 0;
    double vz = 0;
    double acx = 0;
    double acy = 0;
    double acz = 0;
    double densidad = 0;

    Particula() = default;
    void printinfo(int counter) const;
    void set_particles_coordinates(std::ifstream & file);
    static double calculo_i (double px, double sx, double xmin);
    static double calculo_j (double py, double sy, double ymin);
    static double calculo_k (double pz, double sz, double zmin);
    [[nodiscard]] std::string particle_write() const;
};

#endif  // FLUID_PARTICLE_HPP
