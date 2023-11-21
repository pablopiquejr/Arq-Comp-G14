#!/bin/sh
. /etc/profile
module avail
module load gcc/12.1.0
cd build_debug
valgrind --tool=cachegrind --cachegrind-out-file=large5  ./fluid/fluid 10 ../../large.fld ../../output.fld
cg_annotate large5 --auto=yes
