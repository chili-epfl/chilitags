#!/bin/sh -l

set -e # fail on error

echo $PATH

export $PATH=$PATH;/opt/ros/kinetic/bin
echo $PATH

mkdir build
cd build
pwd
cmake ..
make