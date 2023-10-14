//
// Created by sergio on 3/10/23.
//
#include "grid.hpp"
// SE PASA DE COMPLEJIDAD
void incremento_aceleracion(Particula & particula_i, Particula & particula_j, double norma) {
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
  incremento_aceleracion(particula_i, particula_j,norma);
}
//ESTAS DOS FUNCIONES ERAN DE BLOQUE
// SI USAS DATOS DE PARTICULA PIENSA SI RENTA MAS TENER ESTA FUNCIÓN DENTRO DE LA CLASE
void Cubo::transformacion_densidad(Particula & particula) {
  // SI aqui usas PI, creo que hay una libreria para eso, deberias usarla
  particula.densidad = (particula.densidad + std::pow(h_logitud_suavizado, 6)) *
                       315 * m_particula / (64 * std::numbers::pi * std::pow(h_logitud_suavizado, 9));
}

void Cubo::movimiento_particulas(Particula & particula_i) {
  particula_i.px      += particula_i.hvx * a_tiempo + particula_i.acx * pow(a_tiempo, 2);
  particula_i.py      += particula_i.hvy * a_tiempo + particula_i.acy * pow(a_tiempo, 2);
  particula_i.pz      += particula_i.hvz * a_tiempo + particula_i.acz * pow(a_tiempo, 2);
  // se puede cambiar la división por * 0.5
  particula_i.vx       = particula_i.hvx + particula_i.acx * a_tiempo * 2;
  particula_i.vy       = particula_i.hvy + particula_i.acy * a_tiempo / 2;
  particula_i.vz       = particula_i.hvz + particula_i.acz * a_tiempo / 2;
  particula_i.hvx     += particula_i.acx * a_tiempo;
  particula_i.hvy     += particula_i.acy * a_tiempo;
  particula_i.hvz     += particula_i.acz * a_tiempo;
}
void Cubo::set_grid_values() {
  n_x = floor((x_max - x_min) / h_logitud_suavizado);
  n_y = floor((y_max - y_min) / h_logitud_suavizado);
  n_z = floor((z_max - z_min) / h_logitud_suavizado);

}

void Cubo::creacion_bloques(std::vector<Particula>list_of_particles){
    for (int i = 0;i < n_x;i++){
      for (int j=0; j < n_y; j++){
        for (int k= 0; k < n_z; k++){
          Bloque bloque(i, j, k);
          bloques.push_back(bloque);
        }
      }
    }
    asignacion_inicial(list_of_particles);
}
void Cubo:: asignacion_inicial(std::vector<Particula>list_of_particles){
    for (Particula particula:list_of_particles){
        set_particles_coordinates(particula);
        for (Bloque bloque: bloques){
            if (particula.i==bloque.b_x_coordinate && particula.j==bloque.b_y_coordinate &&
            particula.k==bloque.b_z_coordinate){
                bloque.lista_particulas.push_back(particula);
            }
        }
    }
}

void Cubo::choques_entre_particulas(){
    for (Bloque bloque: bloques){
        for (Bloque bloque2: bloques){
            if (bloque.b_x_coordinate==bloque2.b_x_coordinate-1 || bloque.b_x_coordinate==bloque2.b_x_coordinate ||
            bloque.b_x_coordinate==bloque2.b_x_coordinate+1 || bloque.b_y_coordinate==bloque2.b_y_coordinate-1 ||
            bloque.b_y_coordinate==bloque2.b_y_coordinate || bloque.b_y_coordinate==bloque2.b_y_coordinate+1 ||
            bloque.b_z_coordinate==bloque2.b_z_coordinate-1 || bloque.b_z_coordinate==bloque2.b_z_coordinate ||
            bloque.b_z_coordinate==bloque2.b_z_coordinate+1){
                for (Particula particula: bloque.lista_particulas ){
                    for (Particula particula2: bloque2.lista_particulas ){
                        if (particula.identifier<particula2.identifier){
                            incremento_densidades(particula,particula2);
                            movimiento_particulas(particula);
                            movimiento_particulas(particula2);
                            transformacion_densidad(particula);
                            transformacion_densidad(particula2);
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
