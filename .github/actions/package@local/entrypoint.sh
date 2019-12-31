#!/bin/bash

# Makes and Creates a debian package
# This script works in a local docker container or with it's Github action.yml
# ./build directory is cleaned every time
# the version generated is only for development builds currently


set -e # fail on error

# the git root is always mapped to the docker's /root 
cd /github/workspace

source /opt/ros/kinetic/setup.bash


#see action.yml for inputs

author=${1:-$(whoami)} # who triggered the build
github_ref=$2 # the branch, tag or pull request path

# the directory where the artifact should be copied so other actions can access
# see also https://medium.com/@fonseka.live/sharing-data-in-github-actions-a9841a9a6f42
staging_dir=${3:-'./build'} 


apt-get -y update
apt-get -y install javahelper # required for debhelper

project_name="$(basename $(git config remote.origin.url |sed "s/\.git$//"))"
timestamp=$(date +%Y%m%d%H%M%S)
build_number=$(echo $github_ref | cut -d'/' -f3) # refs/pull/2/merge is actually pr# until build numbers are available

if [[ -z $build_number ]]; then
    build_number=1
fi

version="$build_number-$author-$timestamp"
echo "chilitags ($version) unstable; urgency=low" > debian/changelog


fakeroot debian/rules clean #ensures no residue
fakeroot debian/rules binary #performs the package

artifact_filename=$(ls .. | grep $project_name) #the package is generated in base directory
artifact_path="$staging_dir/$artifact_filename"
mv "../$artifact_filename" $staging_dir

#show the details of the file FYI
ls -lh $artifact_path

echo ::set-output name=artifact-path::$artifact_path  #reference available to other actions

