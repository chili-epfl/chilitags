

Chilitags is not packaged so AutoModality packages our fork for easy and quick builds.

![Package Workflow Status](https://github.com/AutoModality/chilitags/workflows/Development%20Package/badge.svg)

[![Latest Version @ Cloudsmith](https://api-prd.cloudsmith.io/badges/version/automodality/dev/deb/chilitags/latest/d=ubuntu%252Fxenial;t=1/?render=true&badge_token=gAAAAABeCtIpEQj1ME47SUCAsKR-PfhDmeaDVwD07FpG69sqUpxPR-TpVSRMu9t-SgIEvoQlGOMoOihctK2VdLAk5Av_8wZ7qYNyYF0DrMqEraFkkBOd_g4%3D)](https://cloudsmith.io/~automodality/repos/dev/packages/detail/deb/chilitags/latest/d=ubuntu%252Fxenial;t=1/)

# Build and Deploy

Run the build in a ros docker container. 
```
docker run -it -v ~/am/github/chilitags/:/root --env user=$USER --env CLOUDSMITH_API_KEY={replace with yours} ros:kinetic-perception /root/.github/actions/package@local/entrypoint.sh
```

1. Runs Make
1. Packages the Binary
1. Deploys the Binary to the package repository


# Continous Integration

```
.github/build-deploy.yml
```

Ran by Github Actions Workflow to execute the docker command in a similar fashion.


