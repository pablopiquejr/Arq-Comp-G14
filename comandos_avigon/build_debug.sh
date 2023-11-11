#!/bin/sh
. /etc/profile
module avail
module load gcc/12.1.0
cmake --version
cmake -S .. -B build_debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build_debug

