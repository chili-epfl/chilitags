#!/bin/bash

set -e # fail on error

mkdir build
cd build
pwd
cmake ..
make