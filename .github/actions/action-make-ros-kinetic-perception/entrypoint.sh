#!/bin/sh -l

set -e # fail on error

mkdir build
cd build
cmake ..
make