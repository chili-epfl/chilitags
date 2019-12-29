#!/bin/bash

set -e # fail on error

#see action.yml for inputs

author=$1 # who triggered the build
github_ref=$2 # the branch, tag or pull request path

source /opt/ros/kinetic/setup.bash # to find opencv

apt-get -y update
apt-get -y install javahelper # required for debhelper

project_name="$(basename $(git config remote.origin.url |sed "s/\.git$//"))"
timestamp=$(date +%Y%m%d%H%M%S)
build_number=$(echo $github_ref | cut -d'/' -f3) # refs/pull/2/merge is actuall pr# until build numbers are available
version="$build_number-$author-$timestamp"
echo "$version"
echo "chilitags ($version) unstable; urgency=low" > debian/changelog


fakeroot debian/rules clean #ensures no residue
fakeroot debian/rules binary #performs the package

artifact_filename=$(ls .. | grep $project_name) #the package is generated in base directory

echo ::set-output name=artifact-path::$artifact_filename  #action syntax for passing out variables