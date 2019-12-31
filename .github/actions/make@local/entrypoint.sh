#!/bin/bash

set -e # fail on error

cd /root

rm -rf build #clean the build
mkdir build
cd build
pwd
cmake ..
make
