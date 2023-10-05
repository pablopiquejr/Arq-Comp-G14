//
// Created by sergio on 5/10/23.
//

#ifndef FLUID_PARTICLE_HPP
#define FLUID_PARTICLE_HPP

#include <iostream>

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
    double acx = 0;
    double acy = 0;
    double acz = 0;
    double densidad = 0;

  public:
    Particula() = default;
    void printinfo(int counter) const;
    void set_particles_coordinates(std::istream & file);
};

#endif  // FLUID_PARTICLE_HPP
