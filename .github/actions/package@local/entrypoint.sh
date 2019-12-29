#!/bin/bash

set -e # fail on error

apt-get -y update
apt-get -y install javahelper # required for debhelper
apt-get -y install libopencv-dev

project_name="$(basename $(git config remote.origin.url |sed "s/\.git$//"))"
timestamp=$(date +%Y%m%d%H%M%S)
version="$timestamp"
echo "$project_name $version"
echo "chilitags (0.0.0-12345) unstable; urgency=low" > debian/changelog


fakeroot debian/rules clean
fakeroot debian/rules binary
