#!/bin/sh -l

set -e # fail on error

pwd
ls
mkdir build
cd build
cmake ..
make