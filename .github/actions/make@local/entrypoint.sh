#!/bin/bash

set -e # fail on error

pwd

rm -rf build #clean the build
mkdir build
cd build
pwd
cmake ..
make
