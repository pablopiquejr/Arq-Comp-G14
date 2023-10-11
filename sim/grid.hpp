//
// Created by sergio on 3/10/23.
//

#ifndef LAB_ARQUITECTURA_GRID_HPP
#define LAB_ARQUITECTURA_GRID_HPP
class Cubo {
    private:
        int nx = 0;
        int ny = 0;
        int nz = 0;
    public:
    Cubo() = default;
    double calculo_nx(double xmax, double xmin, double h);
    double calculo_ny(double ymax, double ymin, double h);
    double calculo_nz(double zmax, double zmin, double h);

};
#endif  // LAB_ARQUITECTURA_GRID_HPP
