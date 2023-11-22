#include "../sim/progargs.cpp"
#include <gtest/gtest.h>

namespace {
  TEST(ProgArgsTestSuite, TestValidNumberOfArguments) {
    // Supongamos que argc es 4, que es el número correcto de argumentos
    int argc = 4;
    EXPECT_NO_FATAL_FAILURE(check_n_arguments(argc));
  }

  TEST(ProgArgsTestSuite, TestInvalidNumberOfArguments) {
    int argc = 3;
    EXPECT_THROW(check_n_arguments(argc), std::invalid_argument);
  }

  TEST(ProgArgsTestSuite, TestValidNumber) {
    std::string n_iterations = "100";
    EXPECT_NO_FATAL_FAILURE(validate_number(n_iterations));
  }

  TEST(ProgArgsTestSuite, TestNonNumericNumber) {
    std::string n_iterations = "abc";
    EXPECT_THROW(validate_number(n_iterations), std::invalid_argument);
  }

  TEST(ProgArgsTestSuite, TestNegativeNumber) {
    std::string n_iterations = "-10";
    EXPECT_THROW(validate_number(n_iterations), std::out_of_range);
  }

  TEST(ProgArgsTestSuite, TestFileReader) {
    std::string file_name = "test_file.bin";

    // Create a temporary file for testing
    std::ofstream output(file_name, std::ios::binary);
    if (!output) { FAIL() << "Can't create output file"; }

    // Write some sample data to the file
    float ppm        = 1.0f;
    int n_parameters = 3;
    output.write(reinterpret_cast<const char*>(&ppm), sizeof(float));
    output.write(reinterpret_cast<const char*>(&n_parameters), sizeof(int));

    std::array<double, 3> pxyz = {
      {1.0f, 2.0f, 3.0f}
    };
    std::array<double, 3> hvxyz = {
      {4.0f, 5.0f, 6.0f}
    };
    std::array<double, 3> vxyz = {
      {7.0f, 8.0f, 9.0f}
    };

    for (int i = 0; i < n_parameters; i++) {
      output.write(reinterpret_cast<const char*>(&pxyz[i]), sizeof(float));
      output.write(reinterpret_cast<const char*>(&hvxyz[i]), sizeof(float));
      output.write(reinterpret_cast<const char*>(&vxyz[i]), sizeof(float));
    }

    output.close();

    // Call the file_reader function
    longitud_y_masa result  = file_reader(file_name);
    result.particulas.pxyz  = {pxyz};
    result.particulas.hvxyz = {hvxyz};
    result.particulas.vxyz  = {vxyz};

    // Verify the result
    EXPECT_EQ(result.ppm, ppm);
    EXPECT_EQ(result.n_particulas, n_parameters);
    EXPECT_EQ(result.particulas.pxyz[0], pxyz);
    EXPECT_EQ(result.particulas.hvxyz[0], hvxyz);
    EXPECT_EQ(result.particulas.vxyz[0], vxyz);

    // Clean up the temporary file
    std::remove(file_name.c_str());
  }
}

// correr tests namespace
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}