#include <fstream>
#include <iostream>
#include <cmath> // esta librería hay que quitarla

using namespace std;

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
    double densidad;
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
        this->densidad = densidad;
    }
};

void argument_validator(char * argv[]){
  // checkjng the validity of the first command (nº of executions)
  if (!stoi(argv[0],0,10)){
    cout << "Time steps must be numeric";
    exit(-1);
  }
  else if (stoi(argv[0], 0, 10) < 0){
    cout << "Invalid number of time steps";
    exit(-2);
  }

  // trying to read the file
  int np;

  ifstream ifs(argv[1],ios_base::openmode(ios_base::binary));

}


int main(int argc, char * argv[]) {

  if (argc != 3){
    cout << "Invalid number of steps: " << argc;
    exit(-1);
  }

  argument_validator(argv);

    // Parser de los comandos:



    // Crear objetos de la clase Particula
    Particula particula1(1.0, 2.0, 3.0, 0.5, 0.6, 0.7, 2.5, 3.5, 4.5);
    Particula particula2(2.0, 3.0, 4.0, 0.7, 0.8, 0.9, 3.5, 4.5, 5.5);
    return 0;
}
double calculo_m(double ppm,double p){
    double ppm_cubo = pow(ppm, 3.0);
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
double incremento_densidades (double h, class particula_i, class particula_j){
        double condicion = pow(particula_i.densidad-particula_j.densidad,2);
        double h_2 = pow(h,2);
        if condition < h_2{
            double incremento= pow(h_2-condicion,3);
            particula_i.densidad+=incremento;
            particula_j.densidad+=incremento;
        }
}
