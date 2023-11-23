//
// Created by sergio on 17/10/23.
//

#ifndef FLUID_SETTER_HPP
#define FLUID_SETTER_HPP

#include "particle.hpp"

#include <cmath>

struct setter {
    // Para generarlo necesitamos el numero de particulas por metro, y el numero total
    explicit setter(float ppm, int numero_p)
      // De esos valores, sacamos la longitud de suavizado, la masa de las particulas y le decimos a
      // la Particula el su tamaño
      : l_suavizado{r_radio / ppm}, masa_p{p_densidad / std::pow(ppm, 3)}, n_particulas{numero_p},
        ppm{ppm}, particulas(numero_p) { }

    double l_suavizado;
    double masa_p;
    int n_particulas;
    float ppm;
    // Tambíen nos podemos ahorrar algunos calculos operando aquí parte del incremento
    double operador_derecha_ac =
        m_num_45 * u_viscosidad * masa_p / (M_PI * std::pow(l_suavizado, m_num_6));
    // Objeto particula sobre el que operaremos
    Particula particulas;
};
#endif  // FLUID_SETTER_HPP
