#!/bin/bash

set -e # fail on error

echo $PATH

source /opt/ros/kinetic/setup.bash
echo $PATH

mkdir build
cd build
pwd
cmake ..
make