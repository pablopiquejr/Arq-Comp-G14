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
}



double calculo_m(double ppm,double p){
  double ppm_cubo = std::pow(ppm, 3.0);
  double masa = p / ppm_cubo;
  return  masa;
}
double calculo_h (double ppm, double r){
  double h = r/ppm;
  return h;
}
double calculo_nx (double xmax, double xmin, double h) {
  double nx = (xmax - xmin) / h;
  return nx;
}
double calculo_ny ( double h ,double ymax, double ymin){
  double ny= (ymax-ymin)/h;
  return ny;
}
double calculo_nz (double h , double zmax, double zmin){
  double nz= (zmax-zmin)/h;
  return nz;
}
double calculo_sx (double nx, double xmax, double xmin){
  double sx= (xmax-xmin)/nx;
  return sx;
}
double calculo_sy (double ny, double ymax, double ymin){
  double sy= (ymax-ymin)/ny;
  return sy;
}
double calculo_sz (double nz, double zmax, double zmin){
  double sz= (zmax-zmin)/nz;
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
double incremento_densidades (double h,class particula_i, class particula_j){
  double norma = std::pow(particula_i.px-particula_j.px,2)+std::pow(particula_i.py-particula_j.py,2)
                 +std::pow(particula_i.pz,particula_j.pz,2);
  double h_2 = pow(h,2);
  if (norma < h_2){
    double incremento= pow(h_2-norma,3);
    particula_i.densidad+=incremento;
    particula_j.densidad+=incremento;
  }
}
double incremento_aceleracion (class particula_i, class particula_j, double h, double norma){
    double distancia= pow(max(norma,std::pow(10,-12),0.5);
    double operador_izquierda= 15*m*std::pow(h-distancia,2)* (particula_i.densidad + particula_j.densidad- 2*(std::pow(10,-3)))
                               / (3.14*std::pow(h,6)*distancia);
    double operador_derecha= 45*0.4*m/(3.14*std::pow(h,6));
    double incremento_aceleracion_iz_x=(particula_i.px-particula_j.px)*operador_izquierda;
    double incremento_aceleracion_iz_y=(particula_i.py-particula_j.py)*operador_izquierda;
    double incremento_aceleracion_iz_z=(particula_i.pz-particula_j.pz)*operador_izquierda;
    double incremento_aceleracion_der_x=(particula_j.vx-particula_i.vx)*operador_derecha;
    double incremento_aceleracion_der_y=(particula_j.vy-particula_i.vy)*operador_derecha;
    double incremento_aceleracion_der_z=(particula_j.vz-particula_i.vz)*operador_derecha;
    double incremento_aceleracion_x= (incremento_aceleracion_iz_x+incremento_aceleracion_der_x)/(particula_i.densidad*particula_j.densidad);
    double incremento_aceleracion_y= (incremento_aceleracion_iz_y+incremento_aceleracion_der_y)/(particula_i.densidad*particula_j.densidad);
    double incremento_aceleracion_z= (incremento_aceleracion_iz_z+incremento_aceleracion_der_z)/(particula_i.densidad*particula_j.densidad);
    particula_i.acx+=incremento_aceleracion_x;
    particula_j.acx+=incremento_aceleracion_x;
    particula_i.acy+=incremento_aceleracion_y;
    particula_j.acy+=incremento_aceleracion_y;
    particula_i.acz+=incremento_aceleracion_z;
    particula_j.acz+=incremento_aceleracion_z;
}
double transformacion_densidad (double densidad, double h, double m){
    densidad= (densidad+ std::pow(h,6))* 315 * m / (64*3.14* std::pow(h,9));
    return densidad;
}
double collision_x(class particula, double xmin, double xmax, double h ){//o mejor llamar a la funcion nx aqui//
    double x= particula.x+ particula.hvx+; //delta de t no va a ser 1 siempre?//
    double nx= calculo_nx(xmin,xmax,h);
    double dp= std::pow(10,-3);
    double cs= 3*std::pow(10,4);
    double dv= 128.0
        if (cx=0){
    double incremento_x= dp-x+xmin;
    if incremento>dp{
          particula.acx+= cs*incremento_x-dv*particula.vx
        };
    }
    if (cx= nx-1){
    double incremento_x= dp-xmax+x;
    if incremento>dp{
          particula.acx-= cs*incremento_x+dv*particula.vx
        };
    }
}
double collision_y(class particula, double ymin, double ymax, double h ){//o mejor llamar a la funcion nx aqui//
    double y= particula.y+ particula.hvy+; //delta de t no va a ser 1 siempre?//
    double ny= calculo_ny(ymin,ymax,h);
    double dp= std::pow(10,-3);
    double cs= 3*std::pow(10,4);
    double dv= 128.0
        if (cx=0){
    double incremento_y= dp-y+ymin;
    if incremento>dp{
          particula.acy+= cs*incremento_y-dv*particula.vy
        };
    }
    if (cy= ny-1){
    double incremento_y= dp-ymax+y;
    if incremento>dp{
          particula.acy-= cs*incremento_y+dv*particula.vy
        };
    }
}
double collision_z(class particula, double zmin, double zmax, double h ){//o mejor llamar a la funcion nx aqui//
    double z= particula.z+ particula.hvz+; //delta de t no va a ser 1 siempre?//
    double nz= calculo_nz(zmin,zmax,h);
    double dp= std::pow(10,-3);
    double cs= 3*std::pow(10,4);
    double dv= 128.0
        if cz=0{
    double incremento_z= dp-z+zmin;
    if incremento>dp{
          particula.acz+= cs*incremento_z-dv*particula.vz
        };
    }
    if (cz= nz-1){
    double incremento_z= dp-zmax+z;
    if incremento>dp{
          particula.acz-= cs*incremento_z+dv*particula.vz
        };
    }
}
double colision_x1(class particula, double xmin, double xmax){
    if (cx=0){
    double dx= particula.x-xmin;
    if dx>=0{
        return;
      }
        else{
      particula.x=xmin-dx;
    }
    }
    if (cx=nx-1){
    double dx= xmax-particula.x;
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
double colision_y1(class particula, double ymin, double ymax){
    if (cy=0){
    double dy= particula.y-ymin;
    if dy>=0{
        return;
      }
        else{
      particula.y=ymin-dy;
    }
    }
    if (cy=ny-1){
    double dy= ymax-particula.y;
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
double colision_z1(class particula, double zmin, double zmax){
    if (cz=0){
    double dz= particula.z-zmin;
    if dz>=0{
        return;
      }
        else{
      particula.z=zmin-dz;
    }
    }
    if (cz=nz-1){
    double dz= zmax-particula.z;
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

