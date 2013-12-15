Chilitags have been extensively used in the past years, providing "real word"
tests. Automated tests are a more recent addition.

To run automated tests, you need to activate them in the CMake configuration
(option `WITH_TESTS`). The test data is in a [separate repository](https://github.com/chili-epfl/chilitags-testdata).
The easiest is to clone it in a directory at the same level as your local copy
of Chilitags; otherwise you can configure the path in the CMake `TEST_DATA`
variable. Then you can run the test suite using CMake's test target.

Example on Unix :
```
git clone git@github.com:chili-epfl/chilitags
git clone git@github.com:chili-epfl/chilitags-testdata.git
cd chilitags
mkdir build
cd build
ccmake .. # set the option `WITH_TESTS` to `ON`
make
make test
```
