#!/bin/sh

# Makes the package, then generates the binary package and deploys it to the repository
# Run this script in a docker container by mapping your source directory to it's root folder
# docker run -v ~/{path}/chilitags/:/root ros:kinetic-perception /root/build.sh

set -e # fail on error

# user - environment variable representing the person triggering the build

# the change log indicates the project name and version
write_changelog(){
    project_name="$(basename $(git config remote.origin.url |sed "s/\.git$//"))"
    timestamp=$(date +%Y%m%d%H%M%S)
    version="$timestamp-$user"
    echo "$project_name ($version) unstable; urgency=low" > debian/changelog
}

# make and create the debian package locally 
create_package(){
    apt-get -y update
    apt-get -y install javahelper # required for debhelper
    fakeroot debian/rules clean
    fakeroot debian/rules binary
}

# send the package to the repository
push_package(){
    # prepare tools for deployment to cloudsmith
    apt-get -y install python-pip
    pip install cloudsmith-cli
    # requires a CLOUDSMITH_API_KEY env variable to pushx
    cloudsmith push deb automodality/trial/ubuntu/xenial ../chilitags_*
}

cd /root
write_changelog
create_package
push_package