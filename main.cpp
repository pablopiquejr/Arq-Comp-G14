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
    Particula(double px,double py,double pz,double hvx,double hvy,double hvz,double vx,double vy,double vz){
        this->px = px;
        this->py = py;
        this->pz = pz;
        this->hvx = hvx;
        this->hvy = hvy;
        this->hvz = hvz;
        this->vx = vx;
        this->vy = vy;
        this->vz = vz;
    }
};
int main() {
    // Crear objetos de la clase Particula
    Particula particula1(1.0, 2.0, 3.0, 0.5, 0.6, 0.7, 2.5, 3.5, 4.5);
    Particula particula2(2.0, 3.0, 4.0, 0.7, 0.8, 0.9, 3.5, 4.5, 5.5);
    return 0;
}
double calculo_masa(double ppm,double p){
    double ppm_cubo = std::pow(ppm, 3.0);
    double masa = p / ppm_cubo;
    return  masa;
}
double calculo_h (double ppm, double r){
    double h = r/ppm;
    return h;
}
double calculo_nx (double xmax, double xmin, double h ,double ymax, double ymin, double zmax, double zmin) {
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
    double i= (px-zmin)/nz;
    return sz;
}
double calculo_j (double nz, double zmax, double zmin){
    double sz= (zmax-zmin)/nz;
    return sz;
}
double calculo_k (double nz, double zmax, double zmin){
    double sz= (zmax-zmin)/nz;
    return sz;
}