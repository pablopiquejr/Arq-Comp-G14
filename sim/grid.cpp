//
// Created by sergio on 3/10/23.
//
#include "grid.hpp"

void Cubo::set_grid_values() {
  n_x = floor((x_max - x_min) / h_logitud_suavizado);
  n_y = floor((y_max - y_min) / h_logitud_suavizado);
  n_z = floor((z_max - z_min) / h_logitud_suavizado);
}

void Cubo::creacion_bloques(){
    for (int i = 0;i < n_x;i++){
      for (int j=0; j < n_y; j++){
        for (int k= 0; k < n_z; k++){
          Bloque const bloque(i, j, k);
          bloques.push_back(bloque);
        }
      }
    }
};

void Cubo::set_particles_coordinates(Particula &particula) const {
    particula.i = floor((particula.px - x_min) * n_x / (x_max - x_min))  ;
    particula.j = floor((particula.py - y_min) * n_y / (y_max - y_min));
    particula.k = floor((particula.pz - z_min)* n_z / (z_max - z_min));
}

void Cubo::colision_x1(Particula &particula, Bloque &bloque) const{
    if (bloque.b_x_coordinate==0){
      // Aquí ponía particula.x, supongo que se referia a px
      double const d_x= particula.px-x_min;
      if (d_x<0){
        // Aquí ponía particula.x, supongo que se referia a px
        particula.px=x_min-d_x;
      }
      return;
    }
    // Que es n_x????
    if (bloque.b_x_coordinate==n_x-1){
      // Aquí ponía particula.x, supongo que se referia a px
      double const d_x= x_max-particula.px;
      if (d_x<0){
        // Aquí ponía particula.x, supongo que se referia a px
        particula.px=x_max+d_x;
      }
      return;
    }
    particula.vx=-particula.vx;
    particula.hvx=-particula.hvx;
}
void Cubo::colision_y1(Particula &particula, Bloque &bloque) const{
    if (bloque.b_y_coordinate==0){
      // Aquí ponía particula.y, supongo que se referia a py
      double const d_y= particula.py-y_min;
      if (d_y<0){
        // Aquí ponía particula.y, supongo que se referia a py
        particula.py=y_min-d_y;
      }
      return;
    }
    if (bloque.b_y_coordinate==n_y-1){
      // Aquí ponía particula.y, supongo que se referia a py
      double const d_y= y_max-particula.py;
      if (d_y<0) {
        // Aquí ponía particula.y, supongo que se referia a py
        particula.py = y_max + d_y;
      }
      return;
    }
    particula.vy=-particula.vy;
    particula.hvy=-particula.hvy;
}
void Cubo::colision_z1(Particula &particula, Bloque &bloque) const{
    if (bloque.b_z_coordinate==0){
      // Aquí ponía particula.z, supongo que se referia a pz
      double const d_z= particula.pz-z_min;
      if (d_z < 0) {
        // Aquí ponía particula.z, supongo que se referia a pz
        particula.pz = z_min - d_z;
      }
      return;
    }

    if (bloque.b_z_coordinate == n_z-1){
      // Aquí ponía particula.z, supongo que se referia a pz
      double const d_z= z_max-particula.pz;
      if (d_z < 0){
        // Aquí ponía particula.z, supongo que se referia a pz
        particula.pz=z_max+d_z;
      }
      return;
    }
    particula.vz=-particula.vz;
    particula.hvz=-particula.hvz;
}
//TEN EN CUENTA QUE ESTO ES PARTE DE LA FUNCION BLOQUE, NO TIENE n_x
void Cubo::colision_x(Particula &particula, Bloque &bloque) const {
    particula.px = particula.px + particula.hvx * a_tiempo;  // delta de t no va a ser 1 siempre?//

    if (bloque.b_x_coordinate == 0) {
      double const incremento_x = d_p - particula.px + x_min;
      if (incremento_x > d_p) { particula.acx += s_c * incremento_x - d_v * particula.vx; }
      if (bloque.b_y_coordinate == n_x - 1) {
        double const incremento_x = d_p - x_max + particula.px;
        if (incremento_x > d_p) { particula.acx -= s_c * incremento_x + d_v * particula.vx; }
      }
    }
}
void Cubo::colision_y(Particula & particula, Bloque &bloque) const {
    particula.py    = particula.py + particula.hvy * a_tiempo;  // delta de t no va a ser 1 siempre?//

    if (bloque.b_y_coordinate == 0) {
      double const incremento_y = d_p - particula.py + y_min;
      if (incremento_y > d_p) { particula.acy += s_c * incremento_y - d_v * particula.vy; }
    }
    if (bloque.b_y_coordinate == n_y - 1) {
      double const incremento_y = d_p - y_max + particula.py;
      if (incremento_y > d_p) { particula.acy -= s_c * incremento_y + d_v * particula.vy; }
    }
}

void Cubo::colision_z(Particula & particula, Bloque &bloque) const {
    // era double const z
    // Aquí ponía particula.z, supongo que se referia a pz
    particula.pz    = particula.pz + particula.hvz * a_tiempo;  // delta de t no va a ser 1 siempre?//

    if (bloque.b_z_coordinate == 0) {
      double const incremento_z = d_p - particula.pz + z_min;
      if (incremento_z > d_p) { particula.acz += s_c * incremento_z - d_v * particula.vz; };
    }
    if (bloque.b_z_coordinate == n_z - 1) {
      double const incremento_z = d_p - z_max + particula.pz;
      if (incremento_z > d_p) { particula.acz -= s_c * incremento_z + d_v * particula.vz; };
    }
}
