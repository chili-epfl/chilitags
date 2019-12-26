#!/bin/sh

# Makes the package, then generates the binary package and deploys it to the repository
# Run this script in a docker container by mapping your source directory to it's root folder
# docker run -v ~/{path}/chilitags/:/root ros:kinetic-perception /root/build.sh

set -e # fail on error

cd /root

# build the binary from the source directory

apt-get -y update
apt-get -y install javahelper # required for debhelper
fakeroot debian/rules clean
fakeroot debian/rules binary

# prepare tools for deployment to cloudsmith
apt-get -y install python-pip
pip install cloudsmith-cli
# requires a CLOUDSMITH_API_KEY env variable to pushx
cloudsmith push deb automodality/trial/ubuntu/xenial ../chilitags_*
