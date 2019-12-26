#!/bin/sh

set -e # fail on error

mkdir build
cd build
cmake ..
make

apt-get -y install fakeroot

fakeroot debian/rules binary