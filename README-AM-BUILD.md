

Chilitags main project is not packaged so AutoModality packages our fork for easy and quick builds.

# Team Development

You must work in a story branch named after your JIRA issue(XX-###). Let Github do the build and validate your changes.

## Make a Story

Runs every `push` to your story branch to compile and test your code. 

![Make Workflow Status](https://github.com/AutoModality/chilitags/workflows/Story/badge.svg)

## Package a Story

Runs only in a `pull_request` or when a pull_request is updated with a `push`.  The artifcat is deployed to Cloudsmith Development Repository where less stable artifacts are shared.

The package should be tested with other systems prior to merging the pull request. 

[![Package Workflow Status](https://github.com/AutoModality/chilitags/workflows/Development%20Package/badge.svg)](https://github.com/AutoModality/chilitags/actions?query=workflow%3A%22Development+Package%22)

[![Latest Version @ Cloudsmith](https://api-prd.cloudsmith.io/badges/version/automodality/dev/deb/chilitags/latest/d=ubuntu%252Fxenial;t=1/?render=true&badge_token=gAAAAABeCtIpEQj1ME47SUCAsKR-PfhDmeaDVwD07FpG69sqUpxPR-TpVSRMu9t-SgIEvoQlGOMoOihctK2VdLAk5Av_8wZ7qYNyYF0DrMqEraFkkBOd_g4%3D)](https://cloudsmith.io/~automodality/repos/dev/packages/detail/deb/chilitags/latest/d=ubuntu%252Fxenial;t=1/)

## Release a Story

Once the package has been tested it is ready to be merged into the mainline `master` branch where it will be released.

# Local Development 

Run the same build scripts locally that Github Actions runs in the cloud. Use docker to ramp up a new container for a clean build every time.

The commands maps your filesystem to the docker's filesystem so the build directory will be generated on your filesystem for easy access. `/github/workspace` is the working directory for Github actions.

## Make

Compiles and tests.

```
cd .github/actions/make\@local/
docker build -t make
docker run -it -v ~/am/github/chilitags/:/github/workspace make 
```

## Package

Generates a package for local testing. The package can be found in the build directory.

```
cd .github/actions/package\@local/
docker build -t package
docker run -it -v ~/am/github/chilitags/:/github/workspace package 
```

A developer could optionally deploy a package to Cloudsmith if such a situation is necessary, although it is recommended to just let Github Actions do the deployment by making a pull request.


