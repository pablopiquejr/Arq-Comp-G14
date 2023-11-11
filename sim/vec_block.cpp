//
// Created by sergio on 4/11/23.
//

#include "vec_block.hpp"
//
// Created by sergio on 3/10/23.
//

void Vec_Bloque::threeD_values(int identifier, std::vector<int> borders){
  b_z = identifier / (borders[0]*borders[1]);
  b_y = (identifier%(borders[0]*borders[1])) / borders[0];
  b_x = (identifier%(borders[0]*borders[1])) % borders[0];
}


void Vec_Bloque::colision_x(int n_x, std::vector<Particula> &Lista_b) {
  for (int &i : lista_particulas) {
    double const const_x = Lista_b[i].pxyz[0] + Lista_b[i].hvxyz[0] * a_tiempo;
    double incremento_x;
    if (n_x == 0) {
      incremento_x = d_p - (const_x - min[0]);
    } else {
      incremento_x = d_p - (max[0] - const_x);
    }
    if (incremento_x > limite_colision) {
      double aumento = s_c * incremento_x - d_v * Lista_b[i].vxyz[0];
      if (n_x != 0) {
        aumento = -s_c * incremento_x - d_v * Lista_b[i].vxyz[0];
      }
      Lista_b[i].a_c[0] += aumento;
    }
  }
}

void Vec_Bloque::colision_y(int n_y, std::vector<Particula> &Lista_b) {
  for (int &i : lista_particulas) {
    double const const_y = Lista_b[i].pxyz[1] + Lista_b[i].hvxyz[1] * a_tiempo;
    double incremento_y;
    if (n_y == 0) {
      incremento_y = d_p - (const_y - min[1]);
    } else {
      incremento_y = d_p - (max[1] - const_y);
    }
    if (incremento_y > limite_colision) {
      double aumento = s_c * incremento_y - d_v * Lista_b[i].vxyz[1];
      if (n_y != 0) {
        aumento = -s_c * incremento_y - d_v * Lista_b[i].vxyz[1];
      }
      Lista_b[i].a_c[1] += aumento;
    }
  }
}

void Vec_Bloque::colision_z(int n_z, std::vector<Particula> &Lista_b) {
  for (int &i : lista_particulas) {
    double const const_z = Lista_b[i].pxyz[2] + Lista_b[i].hvxyz[2] * a_tiempo;
    double incremento_z;
    if (n_z == 0) {
      incremento_z = d_p - (const_z - min[2]);
    } else {
      incremento_z = d_p - (max[2] - const_z);
    }
    if (incremento_z > limite_colision) {
      double aumento = s_c * incremento_z - d_v * Lista_b[i].vxyz[2];
      if (n_z != 0) {
        aumento = -s_c * incremento_z - d_v * Lista_b[i].vxyz[2];
      }
      Lista_b[i].a_c[2] += aumento;
    }
  }
}

void Vec_Bloque::recinto_x(int n_x, std::vector<Particula> &Lista_b) {
  for (int &i : lista_particulas) {
    double d_x;
    if (n_x == 0) {
      d_x = Lista_b[i].pxyz[0] - min[0];
    } else {
      d_x = max[0] - Lista_b[i].pxyz[0];
    }
    if (d_x < 0) {
      if (n_x == 0) {
        Lista_b[i].pxyz[0] = min[0] - d_x;
      } else {
        Lista_b[i].pxyz[0] = max[0] + d_x;
      }
      Lista_b[i].vxyz[0]  = -Lista_b[i].vxyz[0];
      Lista_b[i].hvxyz[0] = -Lista_b[i].hvxyz[0];
    }
  }
}

void Vec_Bloque::recinto_y(int n_y, std::vector<Particula> &Lista_b) {
  for (int &i : lista_particulas) {
    double d_y;
    if (n_y == 0) {
      d_y = Lista_b[i].pxyz[1] - min[1];
    } else {
      d_y = max[1] - Lista_b[i].pxyz[1];
    }
    if (d_y < 0) {
      if (n_y == 0) {
        Lista_b[i].pxyz[1] = min[1] - d_y;
      } else {
        Lista_b[i].pxyz[1] = max[1] + d_y;
      }
      Lista_b[i].vxyz[1]  = -Lista_b[i].vxyz[1];
      Lista_b[i].hvxyz[1] = -Lista_b[i].hvxyz[1];
    }
  }
}

void Vec_Bloque::recinto_z(int n_z, std::vector<Particula> &Lista_b) {
  for (int &i : lista_particulas) {
    double d_z;
    if (n_z == 0) {
      d_z = Lista_b[i].pxyz[2] - min[2];
    } else {
      d_z = max[2] - Lista_b[i].pxyz[2];
    }
    if (d_z < 0) {
      if (n_z == 0) {
        Lista_b[i].pxyz[2] = min[2] - d_z;
      } else {
        Lista_b[i].pxyz[2] = max[2] + d_z;
      }
      Lista_b[i].vxyz[2]  = -Lista_b[i].vxyz[2];
      Lista_b[i].hvxyz[2] = -Lista_b[i].hvxyz[2];
    }
  }
}
