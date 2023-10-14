//
// Created by sergio on 3/10/23.
//
#include "block.hpp"


void Bloque::colision_x_baja()  {
    for (Particula particula: lista_particulas){
        double x = particula.px + particula.hvx * a_tiempo;  // delta de t no va a ser 1 siempre?//
        double incremento_x = d_p - x + x_min;
        if (incremento_x > limite_colision) {
            particula.a_c[0] += s_c * incremento_x - d_v * particula.vx;
        }
        particula.movimiento_particulas();
        double const d_x= particula.px-x_min;
        if (d_x<0){
        particula.px=x_min-d_x;
        }
        particula.vx=-particula.vx;
        particula.hvx=-particula.hvx;
    }
}
void Bloque::colision_y_baja()  {
    for (Particula particula: lista_particulas){
        double y = particula.py + particula.hvy * a_tiempo;  // delta de t no va a ser 1 siempre?//
        double incremento_y = d_p - y + y_min;
        if (incremento_y > limite_colision) {
            particula.a_c[0] += s_c * incremento_y - d_v * particula.vy;
        }
        particula.movimiento_particulas();
        double const d_y= particula.py-y_min;
        if (d_y<0){
        particula.py=y_min-d_y;
        }
        particula.vy=-particula.vy;
        particula.hvy=-particula.hvy;
    }
}
void Bloque::colision_z_baja()  {
    for (Particula particula: lista_particulas){
        double z = particula.pz + particula.hvz * a_tiempo;  // delta de t no va a ser 1 siempre?//
        double incremento_z = d_p - z + z_min;
        if (incremento_z > limite_colision) {
            particula.a_c[0] += s_c * incremento_z - d_v * particula.vz;
        }
        particula.movimiento_particulas();
        double const d_z= particula.pz-z_min;
        if (d_z<0){
        particula.pz=z_min-d_z;
        }
        particula.vz=-particula.vz;
        particula.hvz=-particula.hvz;
    }
}
void Bloque::colision_x_alta()  {
    for (Particula particula: lista_particulas){
        double x = particula.px + particula.hvx * a_tiempo;  // delta de t no va a ser 1 siempre?//
        double incremento_x = d_p - x_max + x;
        if (incremento_x > limite_colision) {
            particula.a_c[0] += -s_c * incremento_x + d_v * particula.vx;
        }
        particula.movimiento_particulas();
        double const d_x= x_max-particula.px;
        if (d_x<0){
        particula.px=x_max+d_x;
        }
        particula.vx=-particula.vx;
        particula.hvx=-particula.hvx;
    }
}
void Bloque::colision_y_alta()  {
    for (Particula particula: lista_particulas){
        double y = particula.py + particula.hvy * a_tiempo;  // delta de t no va a ser 1 siempre?//
        double incremento_y = d_p - y_max + y;
        if (incremento_y > limite_colision) {
            particula.a_c[0] += -s_c * incremento_y + d_v * particula.vy;
        }
        particula.movimiento_particulas();
        double const d_y= y_max-particula.py;
        if (d_y<0){
        particula.py=y_max+d_y;
        }
        particula.vy=-particula.vy;
        particula.hvy=-particula.hvy;
    }
}
void Bloque::colision_z_alta()  {
    for (Particula particula: lista_particulas){
        double z = particula.pz + particula.hvz * a_tiempo;  // delta de t no va a ser 1 siempre?//
        double incremento_z = d_p - z_max + z;
        if (incremento_z > limite_colision) {
            particula.a_c[0] += -s_c * incremento_z + d_v * particula.vz;
        }
        particula.movimiento_particulas();
        double const d_z= z_max-particula.pz;
        if (d_z<0){
        particula.pz=z_max+d_z;
        }
        particula.vz=-particula.vz;
        particula.hvz=-particula.hvz;
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