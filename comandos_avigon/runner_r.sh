#!/bin/sh
. /etc/profile
module avail
module load gcc/12.1.0
cd build
perf stat -r 5 ./fluid/fluid 1000 ../../large.fld ../../output.fld
