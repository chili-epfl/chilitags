#!/bin/bash

set -e # fail on error


author=$1
github_ref=$2

echo "author=$author"
echo "github_ref=$github_ref"

source /opt/ros/kinetic/setup.bash

apt-get -y update
apt-get -y install javahelper # required for debhelper

project_name="$(basename $(git config remote.origin.url |sed "s/\.git$//"))"
timestamp=$(date +%Y%m%d%H%M%S)
version="$timestamp"
echo "$project_name $version"
echo "chilitags (0.0.0-12345) unstable; urgency=low" > debian/changelog


fakeroot debian/rules clean
fakeroot debian/rules binary

artifact_filename=$(ls .. | grep $project_name)

echo ::set-output name=artifact-path::$artifact_filename