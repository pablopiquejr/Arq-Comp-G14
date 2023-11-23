//
// Created by kikealcocerdz on 10/13/23.
//

#ifndef ARQ_COMP_G14_CONSTANTS_HPP
#define ARQ_COMP_G14_CONSTANTS_HPP
#include <array>
#include <cmath>
// Constantes  del problema
double constexpr r_radio      = 1.695;
int constexpr p_densidad      = 1000;
double constexpr p_s          = 3.0;
int constexpr s_c             = 30000;
int constexpr d_v             = 128;
double constexpr u_viscosidad = 0.4;
double constexpr d_p          = 0.0002;
double constexpr a_tiempo     = 0.001;
double constexpr gravedad     = -9.8;

// Coordenadas para el valor máximo de x,y,z
std::array<double, 3> constexpr max = {0.065, 0.1, 0.065};
// Coordenadas para el valor mínimo de x,y,z
std::array<double, 3> constexpr min = {-0.065, -0.08, -0.065};
double const limite_colision        = 0.0000000001;

// Errores de Magic num de clang-tidy
int constexpr m_num_5   = 5;
int constexpr m_num_6   = 6;
int constexpr m_num_9   = 9;
int constexpr m_num_45  = 45;
int constexpr m_num_64  = 64;
int constexpr m_num_315 = 315;
#endif  // ARQ_COMP_G14_CONSTANTS_HPP
