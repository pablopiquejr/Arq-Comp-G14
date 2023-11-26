//
// Created by sergio on 3/10/23.
//

#ifndef LAB_ARQUITECTURA_PROGARGS_HPP
#define LAB_ARQUITECTURA_PROGARGS_HPP

#include "setter.hpp"

#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class progargs {
  public:
    progargs() = default;
    // Comprobar que el numero de argumentos es el esperado
    static void check_n_arguments(int argc);
    // Comprobar que el numero de iteracciones es un integer.
    static void validate_number(std::string const & n_iterations);

    // Leer de tres en tres los datos de las particulas
    static std::array<double, 3> read_data(std::ifstream & file);

    // Escribir, en este caso se podŕia optimizar con array, pero no habría mucha mejora.
    static std::vector<float> write_data(std::array<double, 3> pxyz, std::array<double, 3> hvxyz,
                                         std::array<double, 3> vxyz);
    static struct setter file_reader(std::string const & file_name);

    static struct setter argument_validator(std::vector<std::string> arguments);

    static void file_writer(std::string const & name, setter mis_datos);
};

#endif  // LAB_ARQUITECTURA_PROGARGS_HPP
