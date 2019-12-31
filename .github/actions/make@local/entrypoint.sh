#!/bin/bash

set -e # fail on error

source /opt/ros/kinetic/setup.bash

mkdir build
cd build
pwd
cmake ..
make