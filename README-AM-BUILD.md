
Chilitags is not packaged so AutoModality packages our fork for easy and quick builds.

# Build and Deploy

Run the build in a ros docker container. 
```
docker run -it -v ~/{your path}/chilitags/:/root ros:kinetic-perception /root/build.sh
```

1. Runs Make
1. Packages the Binary
1. Deploys the Binary to the package repository


# Continous Integration

```
.github/build-deploy.yml
```

Ran by Github Actions Workflow to execute the docker command in a similar fashion.


