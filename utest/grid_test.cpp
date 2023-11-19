#include "../sim/vec_grid.cpp"
#include "../sim/progargs.cpp"
#include "../sim/vec_block.cpp"
#include "gtest/gtest.h"

namespace {

  TEST(MovimientoParticulasTestSuite, TestMovimientoParticulas) {
    // Create a Particula object
    Particula particula;

    // Set initial values for the Particula object
    particula.pxyz[0][0] = 1.0;
    particula.pxyz[0][1] = 2.0;
    particula.pxyz[0][2] = 3.0;
    particula.hvxyz[0][0] = 0.5;
    particula.hvxyz[0][1] = 0.5;
    particula.hvxyz[0][2] = 0.5;
    particula.a_c[0][0] = 0.1;
    particula.a_c[0][1] = 0.1;
    particula.a_c[0][2] = 0.1;

    // Call the movimiento_particulas function
    movimiento_particulas(particula, 0);

    // Check the updated values of the Particula object
    EXPECT_EQ(particula.pxyz[0][0], 1.055);
    EXPECT_EQ(particula.pxyz[0][1], 2.055);
    EXPECT_EQ(particula.pxyz[0][2], 3.055);
    EXPECT_EQ(particula.vxyz[0][0], 0.55);
    EXPECT_EQ(particula.vxyz[0][1], 0.55);
    EXPECT_EQ(particula.vxyz[0][2], 0.55);
    EXPECT_EQ(particula.hvxyz[0][0], 0.6);
    EXPECT_EQ(particula.hvxyz[0][1], 0.6);
    EXPECT_EQ(particula.hvxyz[0][2], 0.6);
  }

}  // namespace#include <gtest/gtest.h>
#include "vec_grid.cpp"

// Test case for reposicionar_particula function
TEST(GridTest, ReposicionarParticulaTest) {
  // Create a Grid object
  Grid grid;

  // Create a Particula object
  Particula particula;

  // Set initial values for particula.bpos
  particula.bpos[0][0] = 1.0;
  particula.bpos[0][1] = 2.0;
  particula.bpos[0][2] = 3.0;

  // Call the reposicionar_particula function
  std::vector<double> newpos = {4.0, 5.0, 6.0};
  grid.reposicionar_particula(particula, 0, newpos);

  // Check if the position of the particula has been updated correctly
  EXPECT_EQ(particula.bpos[0][0], 4.0);
  EXPECT_EQ(particula.bpos[0][1], 5.0);
  EXPECT_EQ(particula.bpos[0][2], 6.0);

  // Check if the particula has been moved to the correct block in the grid
  EXPECT_EQ(grid.bloques[grid.transform(4.0, 5.0, 6.0)].lista_particulas[0], 0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}#include <gtest/gtest.h>

// Include the header file for the class being tested
#include "vec_grid.cpp"

// Define a fixture for the tests
class GridTest : public ::testing::Test {
  protected:
    void SetUp() override {
      // Initialize any necessary variables or objects
    }

    void TearDown() override {
      // Clean up any resources used by the tests
    }
};

// Define a test case for the choques_entre_particulas function
TEST_F(GridTest, TestChoquesEntreParticulas) {
  // Arrange
  Grid grid;
  // Initialize the necessary variables and objects for testing

  // Act
  grid.choques_entre_particulas();

  // Assert
  // Add assertions to verify the expected results against the actual results
  // For example:
  // ASSERT_EQ(expected_value, actual_value);
}

// Define a test case for the transferencia_aceleracion function
TEST(GridTest, TransferenciaAceleracion) {
  // Initialize a Grid object with a specific size
  Grid grid(10);

  // Add some particles to the grid
  grid.add_particle(0, 1);
  grid.add_particle(0, 2);
  grid.add_particle(1, 3);
  grid.add_particle(1, 4);

  // Call the transferencia_aceleracion function
  grid.transferencia_aceleracion();

  // Assert that the acceleration of the particles has been updated correctly
  EXPECT_EQ(grid.get_particle_acceleration(0), /* expected acceleration value for particle 0 */);
  EXPECT_EQ(grid.get_particle_acceleration(1), /* expected acceleration value for particle 1 */);
  EXPECT_EQ(grid.get_particle_acceleration(2), /* expected acceleration value for particle 2 */);
  EXPECT_EQ(grid.get_particle_acceleration(3), /* expected acceleration value for particle 3 */);
  EXPECT_EQ(grid.get_particle_acceleration(4), /* expected acceleration value for particle 4 */);
}


// Define a fixture for the tests
class GridTest : public ::testing::Test {
  protected:
    void SetUp() override {
      // Initialize any necessary objects or variables
    }

    void TearDown() override {
      // Clean up any resources used by the tests
    }

    // Define any helper functions or variables needed for the tests
};

// Test case for the incremento_aceleracion function
TEST(GridTestSuite, IncrementoAceleracionTest) {
  // Create a Grid object
  Grid grid;

  // Create a Particula object
  Particula particula;

  // Set up the input parameters
  int index1 = 0;
  int index2 = 1;
  double norma = 1.0;

  // Call the function under test
  grid.incremento_aceleracion(particula, index1, index2, norma);

  // Verify the results

  // Verify the values of var_ac
  std::vector<double> expected_var_ac = {0, 0, 0, 0, 0, 0};
  ASSERT_EQ(particula.var_ac, expected_var_ac);

  // Verify the value of dist
  double expected_dist = std::pow(std::max(norma, std::pow(10, -12)), 0.5);
  ASSERT_EQ(particula.dist, expected_dist);

  // Verify the value of operador_izquierda
  double expected_operador_izquierda =
      (15 * l_m.masa_p * 1.5 * p_s * std::pow(l_m.l_suavizado - expected_dist, 2) *
       (particula.densidad[index1] + particula.densidad[index2] - 2 * p_densidad)) /
      (std::numbers::pi * std::pow(l_m.l_suavizado, 6) * expected_dist);
  ASSERT_EQ(particula.operador_izquierda, expected_operador_izquierda);

  // Verify the value of operador_derecha
  double expected_operador_derecha =
      45 * u_viscosidad * l_m.masa_p / (std::numbers::pi * std::pow(l_m.l_suavizado, 6));
  ASSERT_EQ(particula.operador_derecha, expected_operador_derecha);

  // Verify the values of var_ac[i] and var_ac[i + 3]
  for (int i = 0; i < 3; ++i) {
    double expected_var_ac_i = (particula.pxyz[index1][i] - particula.pxyz[index2][i]) *
                               expected_operador_izquierda;
    double expected_var_ac_i_plus_3 = (particula.vxyz[index2][i] - particula.vxyz[index1][i]) *
                                      expected_operador_derecha;
    ASSERT_EQ(particula.var_ac[i], expected_var_ac_i);
    ASSERT_EQ(particula.var_ac[i + 3], expected_var_ac_i_plus_3);
  }

  // Verify the values of a_c[index1][i] and a_c[index2][i]
  for (size_t i = 0; i < 3; i++) {
    double expected_a_c_index1_i =
        (particula.var_ac[i] + particula.var_ac[i + 3]) /
        (particula.densidad[index1] * particula.densidad[index2]);
    double expected_a_c_index2_i =
        -(particula.var_ac[i] + particula.var_ac[i + 3]) /
        (particula.densidad[index1] * particula.densidad[index2]);
    ASSERT_EQ(particula.a_c[index1][i], expected_a_c_index1_i);
    ASSERT_EQ(particula.a_c[index2][i], expected_a_c_index2_i);
  }
}

// Run the tests
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
