#!/bin/sh -l

set -e # fail on error

apt-get -y update
apt-get -y install javahelper # required for debhelper
fakeroot debian/rules clean
fakeroot debian/rules binary
