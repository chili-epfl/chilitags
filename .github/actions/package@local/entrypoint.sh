#!/bin/bash

set -e # fail on error

#see action.yml for inputs

author=$1 # who triggered the build
github_ref=$2 # the branch, tag or pull request path
staging_dir=$3 # the directory where the artifact should be copied

source /opt/ros/kinetic/setup.bash # to find opencv

apt-get -y update
apt-get -y install javahelper # required for debhelper

project_name="$(basename $(git config remote.origin.url |sed "s/\.git$//"))"
timestamp=$(date +%Y%m%d%H%M%S)
build_number=$(echo $github_ref | cut -d'/' -f3) # refs/pull/2/merge is actuall pr# until build numbers are available
version="$build_number-$author-$timestamp"
echo "chilitags ($version) unstable; urgency=low" > debian/changelog


fakeroot debian/rules clean #ensures no residue
fakeroot debian/rules binary #performs the package

# the file is generated in the home dir, but we are in the build dir still. move it to staging for sharing
artifact_filename=$(ls .. | grep $project_name) #the package is generated in base directory
artifact_path="$staging_dir/$artifact_filename"
mv "../$artifact_filename $artifact_path"
echo ::set-output name=artifact-path::$artifact_path  #action syntax for passing out variables