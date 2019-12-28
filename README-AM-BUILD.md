

Chilitags is not packaged so AutoModality packages our fork for easy and quick builds.

![Package Workflow Status](https://github.com/AutoModality/chilitags/workflows/Package/badge.svg)

[![Latest Version @ Cloudsmith](https://api-prd.cloudsmith.io/badges/version/automodality/trial/deb/chilitags/latest/d=ubuntu%252Fxenial;t=1/?render=true&badge_token=gAAAAABeBuGIDtvuFexlkH8FmguQtuU8ovPJjqOOa6P0gKwEO6_BVCxKjx-EpoGv8ftAG4LsqTua9q-cNFBeeirR3B3zMnnMHVkh9c0BY6ltEqRwa7pkcaI%3D)](https://cloudsmith.io/~automodality/repos/trial/packages/detail/deb/chilitags/latest/d=ubuntu%252Fxenial;t=1/)

# Build and Deploy

Run the build in a ros docker container. 
```
docker run -it -v ~/am/github/chilitags/:/root --env user=$USER --env CLOUDSMITH_API_KEY={replace with yours} ros:kinetic-perception /root/package.sh
```

1. Runs Make
1. Packages the Binary
1. Deploys the Binary to the package repository


# Continous Integration

```
.github/build-deploy.yml
```

Ran by Github Actions Workflow to execute the docker command in a similar fashion.


