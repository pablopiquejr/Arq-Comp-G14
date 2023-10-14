//
// Created by sergio on 3/10/23.
//
#include "grid.hpp"
// SE PASA DE COMPLEJIDAD

/* VERSION PREVIA DE ESTA FUNCIÓN
 * void incremento_aceleracion(Particula & particula_i, Particula & particula_j, double norma) {
// izquierda x,y,z derecha x,y,z
std::vector<double> incremento_aceleracion = {0,0,0,0,0,0};
// vector resultado x,y,z
std::vector<double> incremento_total = {0,0,0};
double const operador_izquierda =
    // el 1.5 es 3/2
    15 * m_particula * 1.5 * p_s * std::pow(h_logitud_suavizado - std::pow(std::max(norma, std::pow(10, -12)), 0.5), 2) *
    (particula_i.densidad + particula_j.densidad - 2 * (std::pow(10, -3))) /
    (std::numbers::pi  * std::pow(h_logitud_suavizado, 6) * std::pow(std::max(norma, std::pow(10, -12)), 0.5));
double const operador_derecha = 45 * 0.4 * m_particula / (std::numbers::pi  * std::pow(h_logitud_suavizado, 6));

 double const incremento_aceleracion_iz_x = (particula_i.px - particula_j.px) * operador_izquierda;
 double const incremento_aceleracion_iz_y = (particula_i.py - particula_j.py) * operador_izquierda;
 double const incremento_aceleracion_iz_z = (particula_i.pz - particula_j.pz) * operador_izquierda;
 double const incremento_aceleracion_der_x = (particula_j.vx - particula_i.vx) * operador_derecha;
 double const incremento_aceleracion_der_y = (particula_j.vy - particula_i.vy) * operador_derecha;
 double const incremento_aceleracion_der_z = (particula_j.vz - particula_i.vz) * operador_derecha;
 double const incremento_aceleracion_x =
     (incremento_aceleracion_iz_x + incremento_aceleracion_der_x) /
     (particula_i.densidad * particula_j.densidad);
 double const incremento_aceleracion_y =
     (incremento_aceleracion_iz_y + incremento_aceleracion_der_y) /
     (particula_i.densidad * particula_j.densidad);
 double const incremento_aceleracion_z =
     (incremento_aceleracion_iz_z + incremento_aceleracion_der_z) /
     (particula_i.densidad * particula_j.densidad);

particula_i.acx  += incremento_aceleracion_x;
particula_j.acx  += incremento_aceleracion_x;
particula_i.acy += incremento_aceleracion_y;
particula_j.acy += incremento_aceleracion_y;
particula_i.acz += incremento_aceleracion_z;
particula_j.acz += incremento_aceleracion_z;
 }
*/

void incremento_aceleracion(Particula & particula_i, Particula & particula_j, double norma) {
  // izquierda x,y,z     derecha x,y,z     resultado x,y,z
  std::vector<double> incremento_aceleracion = {0,0,0,0,0,0, 0,0,0};
  double const operador_izquierda =
      // el 1.5 es 3/2
      15 * m_particula * 1.5 * p_s * std::pow(h_logitud_suavizado-std::pow(std::max(norma,std::pow(10, -12)), 0.5), 2) *
      (particula_i.densidad + particula_j.densidad - 2 * (std::pow(10, -3))) /
      (std::numbers::pi  * std::pow(h_logitud_suavizado, 6) * std::pow(std::max(norma, std::pow(10, -12)), 0.5));
  double const operador_derecha = 45 * 0.4 * m_particula / (std::numbers::pi  * std::pow(h_logitud_suavizado, 6));
  incremento_aceleracion[0] = (particula_i.px - particula_j.px) * operador_izquierda;
  incremento_aceleracion[1] = (particula_i.py - particula_j.py) * operador_izquierda;
  incremento_aceleracion[2] = (particula_i.pz - particula_j.pz) * operador_izquierda;
  incremento_aceleracion[3]  = (particula_j.vx - particula_i.vx) * operador_derecha;
  incremento_aceleracion[4]  = (particula_j.vy - particula_i.vy) * operador_derecha;
  incremento_aceleracion[5]  = (particula_j.vz - particula_i.vz) * operador_derecha;
  incremento_aceleracion[6] = (incremento_aceleracion[0] + incremento_aceleracion[3]) /
                              (particula_i.densidad * particula_j.densidad);
  incremento_aceleracion[7] = (incremento_aceleracion[1] + incremento_aceleracion[4]) /
                              (particula_i.densidad * particula_j.densidad);
  incremento_aceleracion[8] = (incremento_aceleracion[2] + incremento_aceleracion[5]) /
                              (particula_i.densidad * particula_j.densidad);
  for (int i=0; i < 3; ++i){
    particula_i.a_c[i] += incremento_aceleracion[i+6];
    particula_j.a_c[i] += incremento_aceleracion[i+6];
  }
}
void incremento_densidades(Particula & particula_i, Particula & particula_j) {
  double const norma = std::pow(particula_i.px - particula_j.px, 2) +
                       std::pow(particula_i.py - particula_j.py, 2) +
                       std::pow(particula_i.pz - particula_j.pz, 2);
  double const h_2 = std::pow(h_logitud_suavizado, 2);
  if (norma < h_2) {
    double const incremento  = std::pow(h_2 - norma, 3);
    particula_i.densidad    += incremento;
    particula_j.densidad    += incremento;
  }
  particula_i.transformacion_densidad();
  particula_j.transformacion_densidad();
  incremento_aceleracion(particula_i, particula_j,norma);
}



void Cubo::set_grid_values() {
  n_x = floor((x_max - x_min) / h_logitud_suavizado);
  n_y = floor((y_max - y_min) / h_logitud_suavizado);
  n_z = floor((z_max - z_min) / h_logitud_suavizado);

}

void Cubo::creacion_bloques(const std::vector<Particula>&list_of_particles){
    for (int i = 0;i < n_x;i++){
      for (int j=0; j < n_y; j++){
        for (int k= 0; k < n_z; k++){
          Bloque const bloque(i, j, k);
          bloques.push_back(bloque);
        }
      }
    }
    asignacion_inicial(list_of_particles);
}
void Cubo:: asignacion_inicial(const std::vector<Particula>&list_of_particles){
    for (Particula particula:list_of_particles){
        set_particles_coordinates(particula);
        for (Bloque bloque: bloques){
            if (particula.i==bloque.b_x && particula.j==bloque.b_y &&
            particula.k==bloque.b_z){
                bloque.lista_particulas.push_back(particula);
            }
        }
    }
}

void Cubo::choques_entre_particulas(){
    // Esto tiene en cuenta consigo mismo tmb eso esta bien?
    for (Bloque const& bloque: bloques){
        for (Bloque const& bloque2: bloques){
            if (bloque.b_x ==bloque2.b_x -1 || bloque.b_x ==bloque2.b_x ||
            bloque.b_x ==bloque2.b_x +1 || bloque.b_y ==bloque2.b_y -1 ||
            bloque.b_y ==bloque2.b_y || bloque.b_y ==bloque2.b_y +1 ||
            bloque.b_z ==bloque2.b_z -1 || bloque.b_z ==bloque2.b_z ||
            bloque.b_z ==bloque2.b_z +1){
                for (Particula particula: bloque.lista_particulas ){
                    for (Particula particula2: bloque2.lista_particulas ){
                        if (particula.identifier<particula2.identifier){
                            incremento_densidades(particula,particula2);

                        }
                    }
                }
            }
        }
    }
}

void Cubo::set_particles_coordinates(Particula &particula) const {
    particula.i = floor((particula.px - x_min) * n_x / (x_max - x_min))  ;
    if (0>particula.i){
        particula.i=0;
    }
    else if (particula.i>n_x-1){
        particula.i=n_x-1;
    }
    particula.j = floor((particula.py - y_min) * n_y / (y_max - y_min));
    if (0>particula.j){
        particula.j=0;
    }
    else if (particula.j>n_y-1){
        particula.j=n_y-1;
    }
    particula.k = floor((particula.pz - z_min)* n_z / (z_max - z_min));
    if (0>particula.k){
        particula.k=0;
    }
    else if (particula.k>n_z-1){
        particula.k=n_z-1;
    }
}

void Cubo::colision_x1(Particula &particula, Bloque &bloque) const{
    if (bloque.b_x ==0){
      // Aquí ponía particula.x, supongo que se referia a px
      double const d_x= particula.px-x_min;
      if (d_x<0){
        // Aquí ponía particula.x, supongo que se referia a px
        particula.px=x_min-d_x;
      }
      return;
    }
    // Que es n_x????
    if (bloque.b_x ==n_x-1){
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
    if (bloque.b_y ==0){
      // Aquí ponía particula.y, supongo que se referia a py
      double const d_y= particula.py-y_min;
      if (d_y<0){
        // Aquí ponía particula.y, supongo que se referia a py
        particula.py=y_min-d_y;
      }
      return;
    }
    if (bloque.b_y ==n_y-1){
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
    if (bloque.b_z ==0){
      // Aquí ponía particula.z, supongo que se referia a pz
      double const d_z= particula.pz-z_min;
      if (d_z < 0) {
        // Aquí ponía particula.z, supongo que se referia a pz
        particula.pz = z_min - d_z;
      }
      return;
    }

    if (bloque.b_z == n_z-1){
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
//ESTA FUNCION ES DIFERENTE A LA COLISION_Y Y COLISION_Z
void Cubo::colision_x(Particula &particula, Bloque &bloque) const {
    particula.px = particula.px + particula.hvx * a_tiempo;  // delta de t no va a ser 1 siempre?//
    double incremento_x = 0;
    if (bloque.b_x == 0) {
      incremento_x = d_p - particula.px + x_min;
      if (incremento_x > d_p) { particula.a_c[0] += s_c * incremento_x - d_v * particula.vx; }
    }
    if (bloque.b_y == n_x - 1) {
      incremento_x = d_p - x_max + particula.px;
      if (incremento_x > d_p) { particula.a_c[0] -= s_c * incremento_x + d_v * particula.vx; }
    }
}

void Cubo::colision_y(Particula & particula, Bloque &bloque) const {
    particula.py    = particula.py + particula.hvy * a_tiempo;  // delta de t no va a ser 1 siempre?//
    double incremento_y = 0;
    if (bloque.b_y == 0) {
      incremento_y = d_p - particula.py + y_min;
      if (incremento_y > d_p) { particula.a_c[1] += s_c * incremento_y - d_v * particula.vy; }
    }
    if (bloque.b_y == n_y - 1) {
      incremento_y = d_p - y_max + particula.py;
      if (incremento_y > d_p) { particula.a_c[1] -= s_c * incremento_y + d_v * particula.vy; }
    }
}

void Cubo::colision_z(Particula & particula, Bloque &bloque) const {
    // era double const z
    // Aquí ponía particula.z, supongo que se referia a pz
    particula.pz    = particula.pz + particula.hvz * a_tiempo;  // delta de t no va a ser 1 siempre?//
    double incremento_z = 0;
    if (bloque.b_z == 0) {
      incremento_z = d_p - particula.pz + z_min;
      if (incremento_z > d_p) { particula.a_c[2] += s_c * incremento_z - d_v * particula.vz; };
    }
    if (bloque.b_z == n_z - 1) {
      incremento_z = d_p - z_max + particula.pz;
      if (incremento_z > d_p) { particula.a_c[2] -= s_c * incremento_z + d_v * particula.vz; };
    }
}
//IDEA: meter el movimiento dentro de colision_baja
void Cubo::colision_limites(){
    for (Bloque const& bloque: bloques){
        if (bloque.b_x == 0){
            //colision_x_baja                 estas dos funciones se podrian fusionar en una para ajustar la complejidad
            //colision_x_baja_pos
        }
        if (bloque.b_x == n_x-1){
            //colision_x_alta
            //colision_x_alta_pos
        }
        if (bloque.b_y == 0){
            //colision_y_baja
            //colision_y_baja_pos
        }
        if (bloque.b_y == n_y-1){
            //colision_y_alta
            //colision_y_alta_pos
        }
        if (bloque.b_z == 0){
            //colision_z_baja
            //colision_z_baja_pos
        }
        if (bloque.b_z == n_z-1){
            //colision_z_alta
            //colision_z_alta_pos
        }
        mover_particulas_bloque(); //no implementada, haria un for en su lista de particulas y moveria todas
    }



}