//
// Created by sergio on 4/11/23.
//

#include "vec_block.hpp"
//
// Created by sergio on 3/10/23.
//

void Vec_Bloque::threeD_values(int identifier, std::array<int,3> borders){
  b_z = identifier / (borders[0]*borders[1]);
  b_y = (identifier%(borders[0]*borders[1])) / borders[0];
  b_x = (identifier%(borders[0]*borders[1])) % borders[0];
}


void Vec_Bloque::colision_x(int n_x, Particula & particula) {
  for (int  const&part : lista_particulas) {
    double const const_x = particula.pxyz[part][0] + particula.hvxyz[part][0] * a_tiempo;
    double incremento_x = 0;
    if (n_x == 0) {
      incremento_x = d_p - (const_x - min[0]);
    } else {
      incremento_x = d_p - (max[0] - const_x);
    }
    if (incremento_x > limite_colision) {
      double aumento = s_c * incremento_x - d_v * particula.vxyz[part][0];
      if (n_x != 0) {
        aumento = -s_c * incremento_x - d_v * particula.vxyz[part][0];
      }
      particula.a_c[part][0] += aumento;
    }
  }
}

void Vec_Bloque::colision_y(int n_y, Particula & particula) {
  for (int const &part : lista_particulas) {
    double const const_y = particula.pxyz[part][1] + particula.hvxyz[part][1] * a_tiempo;
    double incremento_y=0;
    if (n_y == 0) {
      incremento_y = d_p - (const_y - min[1]);
    } else {
      incremento_y = d_p - (max[1] - const_y);
    }
    if (incremento_y > limite_colision) {
      double aumento = s_c * incremento_y - d_v * particula.vxyz[part][1];
      if (n_y != 0) {
        aumento = -s_c * incremento_y - d_v * particula.vxyz[part][1];
      }
      particula.a_c[part][1] += aumento;
    }
  }
}


void Vec_Bloque::colision_z(int n_z, Particula & particula) {
  for (int const &part : lista_particulas) {
    double const const_z = particula.pxyz[part][2] + particula.hvxyz[part][2] * a_tiempo;
    double incremento_z=0;
    if (n_z == 0) {
      incremento_z = d_p - (const_z - min[2]);
    } else {
      incremento_z = d_p - (max[2] - const_z);
    }
    if (incremento_z > limite_colision) {
      double aumento = s_c * incremento_z - d_v * particula.vxyz[part][2];
      if (n_z != 0) {
        aumento = -s_c * incremento_z - d_v * particula.vxyz[part][2];
      }
      particula.a_c[part][2] += aumento;
    }
  }
}


void Vec_Bloque::recinto_x(int n_x, Particula & particula) {
  for (int const &part : lista_particulas) {
    double d_x=0;
    if (n_x == 0) {
      d_x = particula.pxyz[part][0] - min[0];
    } else {
      d_x = max[0] - particula.pxyz[part][0];
    }
    if (d_x < 0) {
      if (n_x == 0) {
        particula.pxyz[part][0] = min[0] - d_x;
      } else {
        particula.pxyz[part][0] = max[0] + d_x;
      }
      particula.vxyz[part][0]  = -particula.vxyz[part][0];
      particula.hvxyz[part][0] = -particula.hvxyz[part][0];
    }
  }
}

void Vec_Bloque::recinto_y(int n_y, Particula & particula) {
  for (int const  &part : lista_particulas) {
    double d_y = 0;
    if (n_y == 0) {
      d_y = particula.pxyz[part][1] - min[1];
    } else {
      d_y = max[1] - particula.pxyz[part][1];
    }
    if (d_y < 0) {
      if (n_y == 0) {
        particula.pxyz[part][1] = min[1] - d_y;
      } else {
        particula.pxyz[part][1] = max[1] + d_y;
      }
      particula.vxyz[part][1]  = -particula.vxyz[part][1];
      particula.hvxyz[part][1] = -particula.hvxyz[part][1];
    }
  }
}

void Vec_Bloque::recinto_z(int n_z, Particula & particula) {
  for (int const &part : lista_particulas) {
    double d_z = 0;
    if (n_z == 0) {
      d_z = particula.pxyz[part][2] - min[2];
    } else {
      d_z = max[2] - particula.pxyz[part][2];
    }
    if (d_z < 0) {
      if (n_z == 0) {
        particula.pxyz[part][2] = min[2] - d_z;
      } else {
        particula.pxyz[part][2] = max[2] + d_z;
      }
      particula.vxyz[part][2]  = -particula.vxyz[part][2];
      particula.hvxyz[part][2] = -particula.hvxyz[part][2];
    }
  }
}

