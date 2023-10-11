//
// Created by sergio on 3/10/23.
//
#include "block.hpp"
void colision_x1(Particula & particula, double xmin, double xmax) {
    if (c_x = 0) {
        double const dx = particula.x - xmin;
        if dx {
                    >= 0 {
                        return;
                    }
            } else {
            particula.x = xmin - dx;
        }
    }
    if (c_x = nx - 1) {
        double const dx = xmax - particula.x;
        if dx {
                    >= 0 {
                        return;
                    }
            } else {
            particula.x = xmax + dx
        }
    }
    particula.vx  = -particula.vx;
    particula.hvx = -particula.hvx
}
void colision_y1(Particula & particula, double ymin, double ymax) {
    if (c_y = 0) {
        double const dy = particula.y - ymin;
        if dy {
                    >= 0 {
                        return;
                    }
            } else {
            particula.y = ymin - dy;
        }
    }
    if (c_y = ny - 1) {
        double const dy = ymax - particula.y;
        if dy {
                    >= 0 {
                        return;
                    }
            } else {
            particula.y = ymax + dy
        }
    }
    particula.vy  = -particula.vy;
    particula.hvy = -particula.hvy
}
void colision_z1(Particula & particula, double zmin, double zmax) {
    if (c_z = 0) {
        double const dz = particula.z - zmin;
        if dz {
                    >= 0 {
                        // RETURN EL Q
                        return;
                    }
            } else {
            particula.z = zmin - dz;
        }
    }
    if (c_z = nz - 1) {
        double const dz = zmax - particula.z;
        if dz {
                    >= 0 {
                        return;  // MAS DE LO MISMO
                    }
            } else {
            particula.z = zmax + dz
        }
    }
    particula.vz  = -particula.vz;
    particula.hvz = -particula.hvz
}
void collision_x(class particula, double xmin, double xmax,double h) {                          // o mejor llamar a la funcion nx aqui//
    particula.px    = particula.px + particula.hvx + ;  // delta de t no va a ser 1 siempre?//
    double const nx = calculo_nx(xmin, xmax, h);
    double const dp = std::pow(10, -3);
    double const cs = 3 * std::pow(10, 4);
    double const dv = 128.0 if (c_x = 0) {
        double const incremento_x = dp - x + xmin;
        if incremento { > dp{particula.ac_x += cs * incremento_x - dv * particula.vx}; }
    }
    if (c_x = nx - 1) {
        double const incremento_x = dp - xmax + x;
        if incremento { > dp{particula.ac_x -= cs * incremento_x + dv * particula.vx}; }
    }
}
void collision_y(class particula, double ymin, double ymax,
                 double h) {                         // o mejor llamar a la funcion nx aqui//
    double const y  = particula.y + particula.hvy + ;  // delta de t no va a ser 1 siempre?//
    double const ny = calculo_ny(ymin, ymax, h);
    double const dp = std::pow(10, -3);
    double const cs = 3 * std::pow(10, 4);
    double const dv = 128.0 if (c_x = 0) {
        double const incremento_y = dp - y + ymin;
        if incremento { > dp{particula.ac_y += cs * incremento_y - dv * particula.vy}; }
    }
    if (c_y = ny - 1) {
        double const incremento_y = dp - ymax + y;
        if incremento { > dp{particula.ac_y -= cs * incremento_y + dv * particula.vy}; }
    }
}
void collision_z(Particula & particula_i, double zmin, double zmax,
                 double h) {                         // o mejor llamar a la funcion nx aqui//
    double const z  = particula.z + particula.hvz + ;  // delta de t no va a ser 1 siempre?//
    double const nz = calculo_nz(zmin, zmax, h);
    double const dp = std::pow(10, -3);
    double const cs = 3 * std::pow(10, 4);
    double const dv = 128.0 if c_z = 0 {
        double const incremento_z = dp - z + zmin;
        if incremento { > dp{particula.ac_z += cs * incremento_z - dv * particula.vz}; }
    }
    if (c_z = nz - 1) {
        double const incremento_z = dp - zmax + z;
        if incremento { > dp{particula.ac_z -= cs * incremento_z + dv * particula.vz}; }
    }
}

/////////////////EJEMPLO DE COMO SE PROGRAMAN LOS TESTS ///////////////////////////

/*#include "block.hpp"
#include "product.h"
#include <gtest/gtest.h>

// https://google.github.io/googletest/reference/assertions.html

namespace
{
    TEST(PersonTestSuite, functionA)
{
    Product p;
    EXPECT_EQ(p.computeA(10, 20), 200);
}
TEST(PersonTestSuite, functionB)
{
Product p;
EXPECT_EQ(p.computeB(10, 20, 30), 6000);
}

TEST(PersonTestSuite, not_equal_functionB)
{
Product p;
EXPECT_NE(p.computeB(10, 20, 30), 5000);
}

TEST(PersonTestSuite, fun_B_greater_funA)
{
Product p;
EXPECT_GT(p.computeB(10, 20, 30), p.computeA(10, 10));
}

}
 */