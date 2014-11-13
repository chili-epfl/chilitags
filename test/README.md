Chilitags have been extensively used in the past years, providing "real word"
tests. Automated tests are a more recent addition.

To run automated tests, you need to activate them in the CMake configuration
(option `WITH_TESTS`). The test data is a submodule, you need to get it before
being able to run tests.

Example on Unix :
```
git clone --recursive git@github.com:chili-epfl/chilitags
cd chilitags
mkdir build
cd build
ccmake .. # set the option `WITH_TESTS` to `ON`
make
cd test && ctest
```

