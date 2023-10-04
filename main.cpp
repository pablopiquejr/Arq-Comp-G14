#include <iostream>
#include <cmath>

class Particula{
public:
    double px;
    double py;
    double pz;
    double hvx;
    double hvy;
    double hvz;
    double vx;
    double vy;
    double vz;
    double acx;
    double acy;
    double acz;
    double densidad;
    Particula(double px,double py,double pz,double hvx,double hvy,double hvz,double vx,double vy,double vz, double acx,
              double acy, double acz, double densidad){
        this->px = px;
        this->py = py;
        this->pz = pz;
        this->hvx = hvx;
        this->hvy = hvy;
        this->hvz = hvz;
        this->vx = vx;
        this->vy = vy;
        this->vz = vz;
        this->acx = acx;
        this->acy = acy;
        this->acz = acz;
        this->densidad = densidad;
    }
};

int main() {
    // Crear objetos de la clase Particula
    Particula particula1(1.0, 2.0, 3.0, 0.5, 0.6, 0.7, 2.5, 3.5, 4.5);
    Particula particula2(2.0, 3.0, 4.0, 0.7, 0.8, 0.9, 3.5, 4.5, 5.5);
    return 0;
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
    double h_2 = std::pow(h,2);
    if norma < h_2{
        double incremento= std::pow(h_2-norma,3);
        particula_i.densidad+=incremento;
        particula_j.densidad+=incremento;
        }
}
double incremento_aceleracion (class particula_i, class particula_j, double h, double norma){
    double distancia= sdd::pow(max(norma,std::pow(10,-12),0.5);
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
    if cx=0{
        double incremento_x= dp-x+xmin;
        if incremento>dp{
            particula.acx+= cs*incremento_x-dv*particula.vx
        };
    }
    if cx= nx-1{
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
    if cx=0{
        double incremento_y= dp-y+ymin;
        if incremento>dp{
                    particula.acy+= cs*incremento_y-dv*particula.vy
            };
    }
    if cy= ny-1{
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
    if cz= nz-1{
        double incremento_z= dp-zmax+z;
        if incremento>dp{
                    particula.acz-= cs*incremento_z+dv*particula.vz
            };
    }
}