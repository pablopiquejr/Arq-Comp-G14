//
// Created by sergio on 5/10/23.
//

#include "particle.hpp"
#include <iostream>
# include <cmath>


void Particula::set_particles_coordinates(std::istream & file) {
  px = read_float(file);
  py = read_float(file);
  pz = read_float(file);
  hvx = read_float(file);
  hvy = read_float(file);
  hvz = read_float(file);
  vx = read_float(file);
  vy = read_float(file);
  vz = read_float(file);
  densidad= 0;
  acx=0;
  acy=0;
  acz=0;
}

void Particula::printinfo(int counter) const{
  std::cout << "Particula" << counter << '\n';
  std::cout << "px:  " << counter << " " << px <<'\n';
  std::cout << "py:  " << counter << " " << py <<'\n';
  std::cout << "pz:  " << counter << " "<< pz <<'\n';
  std::cout << "hvx:  " << counter << " "<< hvx <<'\n';
  std::cout << "hvy " << counter << " "<< hvx <<'\n';
  std::cout << "hvz " << counter << " "<< hvz <<'\n';
  std::cout << "vx:  " << counter << " "<< vx <<'\n';
  std::cout << "vy " << counter << " "<< vx <<'\n';
  std::cout << "vz " << counter << " "<< vz <<'\n';



  double calculo_m(double ppm,double p){
      double const ppm_cubo = std::pow(ppm, 3.0);
      double const masa = p / ppm_cubo;
      return  masa;
    }
double calculo_h (double ppm, double r){
  double const h = r/ppm;
  return h;
}
double calculo_nx (double xmax, double xmin, double h) {
  double const nx = (xmax - xmin) / h;
  return nx;
}
double calculo_ny ( double h ,double ymax, double ymin){
  double const ny= (ymax-ymin)/h;
  return ny;
}
double calculo_nz (double h , double zmax, double zmin){
  double const nz= (zmax-zmin)/h;
  return nz;
}
double calculo_sx (double nx, double xmax, double xmin){
  double const sx= (xmax-xmin)/nx;
  return sx;
}
double calculo_sy (double ny, double ymax, double ymin){
  double const sy= (ymax-ymin)/ny;
  return sy;
}
double calculo_sz (double nz, double zmax, double zmin){
  double const sz= (zmax-zmin)/nz;
  return sz;
}
double calculo_i (double px, double sx, double xmin){
  double i= (px-xmin)/sx;
  return i;
}
double calculo_j (double sy, double py , double ymin){
  double j= (py-ymin)/sy;
  return j;
}
double calculo_k (double sz, double pz, double zmin){
  double k= (pz - zmin)/sz;
  return k;
}
void incremento_densidades (double h, Particula &particula_i, Particula &particula_j) {
    double const norma = pow(particula_i.px - particula_j.px, 2) + pow(particula_i.py - particula_j.py, 2) +
                         pow(particula_i.pz - particula_j.pz, 2);
    double const h_2 = pow(h, 2);
    if (norma < h_2) {
        double const incremento = pow(h_2 - norma, 3);
        particula_i.densidad += incremento;
        particula_j.densidad += incremento;
    }
}

void incremento_aceleracion (Particula &particula_i, Particula &particula_j, double h, double norma, double m){
    double const operador_izquierda = 15 * m * pow(h - pow(max(norma, pow(10, -12)), 0.5), 2) * (particula_i.densidad + particula_j.densidad - 2 * (pow(10, -3))) / (3.14 * pow(h, 6) * pow(max(norma, pow(10, -12)), 0.5));
    double const operador_derecha = 45 * 0.4 * m / (3.14 * pow(h, 6));
    double const incremento_aceleracion_iz_x = (particula_i.px - particula_j.px) * operador_izquierda;
    double const incremento_aceleracion_iz_y = (particula_i.py - particula_j.py) * operador_izquierda;
    double const incremento_aceleracion_iz_z = (particula_i.pz - particula_j.pz) * operador_izquierda;
    double const incremento_aceleracion_der_x = (particula_j.vx - particula_i.vx) * operador_derecha;
    double const incremento_aceleracion_der_y = (particula_j.vy - particula_i.vy) * operador_derecha;
    double const incremento_aceleracion_der_z = (particula_j.vz - particula_i.vz) * operador_derecha;
    double const incremento_aceleracion_x = (incremento_aceleracion_iz_x + incremento_aceleracion_der_x) / (particula_i.densidad * particula_j.densidad);
    double const incremento_aceleracion_y = (incremento_aceleracion_iz_y + incremento_aceleracion_der_y) / (particula_i.densidad * particula_j.densidad);
    double const incremento_aceleracion_z = (incremento_aceleracion_iz_z + incremento_aceleracion_der_z) / (particula_i.densidad * particula_j.densidad);
    particula_i.acx += incremento_aceleracion_x;
    particula_j.acx += incremento_aceleracion_x;
    particula_i.acy += incremento_aceleracion_y;
    particula_j.acy += incremento_aceleracion_y;
    particula_i.acz += incremento_aceleracion_z;
    particula_j.acz += incremento_aceleracion_z;
}
double transformacion_densidad (double densidad, double h, double m){
    densidad= (densidad+ pow(h,6))* 315 * m / (64*3.14* pow(h,9));
    return densidad;
}
}

void Cubo{
    cx=0;
    cy=0;
    cz=0;
            void colision_x1(Particula &particula, double xmin, double xmax){
                if (cx=0){
                    double const dx= particula.x-xmin;
                    if dx>=0{
                        return;
                    }
                    else{
                        particula.x=xmin-dx;
                    }
                }
                if (cx=nx-1){
                    double const dx= xmax-particula.x;
                    if dx>=0{
                        return;
                    }
                    else{
                        particula.x=xmax+dx
                    }
                }
                particula.vx=-particula.vx;
                particula.hvx=-particula.hvx
            }
            void colision_y1(Particula &particula, double ymin, double ymax){
                if (cy=0){
                    double const dy= particula.y-ymin;
                    if dy>=0{
                        return;
                    }
                    else{
                        particula.y=ymin-dy;
                    }
                }
                if (cy=ny-1){
                    double const dy= ymax-particula.y;
                    if dy>=0{
                        return;
                    }
                    else{
                        particula.y=ymax+dy
                    }
                }
                particula.vy=-particula.vy;
                particula.hvy=-particula.hvy
            }
            void colision_z1(Particula &particula, double zmin, double zmax){
                if (cz=0){
                    double const dz= particula.z-zmin;
                    if dz>=0{
                        return;
                    }
                    else{
                        particula.z=zmin-dz;
                    }
                }
                if (cz=nz-1){
                    double const dz= zmax-particula.z;
                    if dz>=0{
                        return;
                    }
                    else{
                        particula.z=zmax+dz
                    }
                }
                particula.vz=-particula.vz;
                particula.hvz=-particula.hvz
            }
        void collision_x(class particula, double xmin, double xmax, double h ){//o mejor llamar a la funcion nx aqui//
            particula.px= particula.px+ particula.hvx+; //delta de t no va a ser 1 siempre?//
            double const nx= calculo_nx(xmin,xmax,h);
            double const dp= pow(10,-3);
            double const cs= 3*pow(10,4);
            double const dv= 128.0
            if (cx=0){
                double const incremento_x= dp-x+xmin;
                if incremento>dp{
                            particula.acx+= cs*incremento_x-dv*particula.vx
                    };
            }
            if (cx= nx-1){
                double const incremento_x= dp-xmax+x;
                if incremento>dp{
                            particula.acx-= cs*incremento_x+dv*particula.vx
                    };
            }
        }
        void collision_y(class particula, double ymin, double ymax, double h ){//o mejor llamar a la funcion nx aqui//
            double const y= particula.y+ particula.hvy+; //delta de t no va a ser 1 siempre?//
            double const ny= calculo_ny(ymin,ymax,h);
            double const dp= std::pow(10,-3);
            double const cs= 3*std::pow(10,4);
            double const dv= 128.0
            if (cx=0){
                double const incremento_y= dp-y+ymin;
                if incremento>dp{
                            particula.acy+= cs*incremento_y-dv*particula.vy
                    };
            }
            if (cy= ny-1){
                double const incremento_y= dp-ymax+y;
                if incremento>dp{
                            particula.acy-= cs*incremento_y+dv*particula.vy
                    };
            }
        }
        void collision_z(Particula &particula_i, double zmin, double zmax, double h ){//o mejor llamar a la funcion nx aqui//
            double const z= particula.z+ particula.hvz+; //delta de t no va a ser 1 siempre?//
            double const nz= calculo_nz(zmin,zmax,h);
            double const dp= std::pow(10,-3);
            double const cs= 3*std::pow(10,4);
            double const dv= 128.0
            if cz=0{
                double const incremento_z= dp-z+zmin;
                if incremento>dp{
                            particula.acz+= cs*incremento_z-dv*particula.vz
                    };
            }
            if (cz= nz-1){
                double const incremento_z= dp-zmax+z;
                if incremento>dp{
                            particula.acz-= cs*incremento_z+dv*particula.vz
                    };
            }


}
