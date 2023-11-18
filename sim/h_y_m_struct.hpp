//
// Created by sergio on 17/10/23.
//

#ifndef FLUID_H_Y_M_STRUCT_HPP
#define FLUID_H_Y_M_STRUCT_HPP

#include "particle.hpp"

#include <cmath>

struct longitud_y_masa{
    explicit longitud_y_masa(float ppm, int numero_p)
      : l_suavizado{r_radio / ppm}, masa_p{p_densidad / std::pow(ppm, 3)}, n_particulas{numero_p},
        ppm{ppm} { }

    Particula particulas;
    double l_suavizado;
    double masa_p;
    int n_particulas;
    float ppm;
    double const operador_derecha_ac =
        45 * u_viscosidad * masa_p / (std::numbers::pi * std::pow(l_suavizado, 6));

};
#endif  // FLUID_H_Y_M_STRUCT_HPP
