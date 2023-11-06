//
// Created by kikealcocerdz on 10/13/23.
//

#ifndef ARQ_COMP_G14_CONSTANTS_HPP
#define ARQ_COMP_G14_CONSTANTS_HPP
#include <cmath>
#include <vector>

double const r_radio         = 1.695;
int const p_densidad         = 1000;
double const p_s             = 3.0;
int const s_c                = 30000;
int const d_v             = 128;
double const u_viscosidad    = 0.4;
double const d_p             = 0.0002;
double const a_tiempo        = 0.001;
double const gravedad        = -9.8;
/*
double const x_max           = 0.065;
double const y_max           = 0.1;
double const z_max           = 0.065;
 */
// Coordinates for the max posible values of x,y,z
std::vector<double> const max = {0.065, 0.1, 0.065};
/*
double const x_min           = -0.065;
double const y_min           = -0.08;
double const z_min           = -0.065;
 */
std::vector<double> const min = {-0.065, -0.08, -0.065};
double const limite_colision = 0.0000000001;

int const m_num_5 = 5;
int const m_num_6 = 6;
int const m_num_7 = 7;
int const m_num_8 = 8;
int const m_num_9 = 9;
#endif  // ARQ_COMP_G14_CONSTANTS_HPP
