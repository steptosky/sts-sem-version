# Cross-platform C++ library for working with Semantic Versioning.


| CI        | master | develop | last commit |
| --------- |:------:|:-------:|:-----------:|
| appveyor  |[![Build status](https://ci.appveyor.com/api/projects/status/2komds1ywr4y4ojp/branch/master?svg=true)](https://ci.appveyor.com/project/steptosky/sts-semver/branch/master)|[![Build status](https://ci.appveyor.com/api/projects/status/2komds1ywr4y4ojp/branch/develop?svg=true)](https://ci.appveyor.com/project/steptosky/sts-semver/branch/develop)|[![Build status](https://ci.appveyor.com/api/projects/status/2komds1ywr4y4ojp?svg=true)](https://ci.appveyor.com/project/steptosky/sts-semver)|
| travis    |[![Build Status](https://travis-ci.org/steptosky/sts-semver.svg?branch=master)](https://travis-ci.org/steptosky/sts-semver)|[![Build Status](https://travis-ci.org/steptosky/sts-semver.svg?branch=develop)](https://travis-ci.org/steptosky/sts-semver)|[![Build Status](https://travis-ci.org/steptosky/sts-semver.svg)](https://travis-ci.org/steptosky/sts-semver)|

---

#### common
- Specification [semver.org](https://semver.org) 
- The library is distributed under 
[BSD (3-Clause)](http://opensource.org/licenses/BSD-3-Clause) 
license for more information read the [license](license.txt) file.
- [SemVer](http://semver.org/) is used for versioning.
- The library requires C++ 11 or higher.
- The versions from the master branch is available in the 
  [bintray](https://bintray.com/steptosky/conan-open-source/sts-semver:steptosky).  
  ```sts-semver/X.Y.Z@steptosky/stable```  

#### warning 
- As the library hasn't got the major version 
  the library's interface and logic aren't stable and can be changed at any time.

---

## Build

#### dependencies
- [Cmake 3.7+](https://cmake.org) - build tool.
- [Conan 1.5+](https://www.conan.io) - the C/C++ package manager.
- [Python 2 or 3](https://www.python.org) - is needed for the Conan.
- [Doxygen](http://www.stack.nl/~dimitri/doxygen) - if you want to generate the documentation.
- [Gtest and Gmock 1.8](https://github.com/google/googletest) - testing (used through the Conan).

#### documentation
Run from the root folder ```doxygen doxyfile``` the result will be in the ```doc-generated``` folder.  
The ```doxygen``` has to be accessible through your ```PATH``` environment variable.


#### conan evironment variables
- **CONAN_TESTING_REPORT_DIR**=(string path) - A path for storing tests results. Default value is specified in the cmake script.
- **CONAN_BUILD_TESTING**=(0 or 1) - Enables/disables building and running the tests.  
  If you set ```BUILD_TESTING=ON``` as a parameter while running ```cmake``` command it will auto-set ```CONAN_BUILD_TESTING=1```.


#### cmake variables
- **BUILD_TESTING**=(ON/OFF) - Enables/disables building test projects. It is standard cmake variable.
- **TESTING_REPORT_DIR**=(string path) - You can specify the directory for the tests reports, it can be useful for CI.

Sometimes you will need to delete the file ```cmake/conan.cmake``` then the newer version of this file will be downloaded from the Internet while running ```cmake``` command.  
This file is responsible for cmake and conan interaction.


### Build scripts examples
These are just examples, 
probably you will need to adjust them for your purposes.


##### Windows (.bat) For Visual Studio 2017
``` batch
::==========================================================
@echo off
:: Fix problems with some symbols
REM change CHCP to UTF-8
CHCP 1252
CLS
::==========================================================
set dir="msvc"
if not exist %dir% mkdir %dir%
cd %dir%
::==========================================================
:: conan user userName -r remote -p password
::==========================================================
call cmake -G "Visual Studio 15 Win64" ../ ^
    -DCMAKE_INSTALL_PREFIX=../output ^
    -DBUILD_TESTING=ON
:: Keep it commented if you want to generate VS project only
:: (without building), otherwise uncomment it.
::call cmake --build . --target install --config Release
::call cmake --build . --target install --config Debug
::==========================================================
cd ../
pause
::==========================================================
```


##### Linux (.sh)
``` bash
#===========================================================
dir_name="build-release"
#===========================================================
rm -r ${dir_name}
mkdir ${dir_name}
cd ${dir_name}
#===========================================================
# conan user userName -r remote -p password
#===========================================================
cmake -G"Unix Makefiles" ../ \
    -DCMAKE_BUILD_TYPE="Release" \
    -DCMAKE_INSTALL_PREFIX=../output \
    -DBUILD_TESTING=ON
cmake --build . --target install
cd ../
#===========================================================
```


##### Mac OS (.sh)
``` bash
#===========================================================
dir_name="build-release"
#===========================================================
rm -r ${dir_name}
mkdir ${dir_name}
cd ${dir_name}
#===========================================================
# conan user userName -r remote -p password
#===========================================================
cmake -G"Unix Makefiles" ../ \
    -DCMAKE_BUILD_TYPE="Release" \
    -DCMAKE_INSTALL_PREFIX=../output \
    -DBUILD_TESTING=ON
cmake --build . --target install
cd ../
#===========================================================
```


#### Build with the conan 'create' and 'conan package tools'.
These are just examples for Windows, 
probably you will need to adjust them for your purposes.


##### Windows (.bat) For Visual Studio 2017 x64

``` batch
::==========================================================
:: conan user userName -r remote -p password
::==========================================================
call conan create . stsff/develop ^
     -s compiler="Visual Studio" ^
     -s compiler.version=15 ^
     -s compiler.runtime=MD ^
     -s build_type=Release ^
     -o stsff-semver:shared=True ^
     -e CONAN_TESTING_REPORT_DIR="report/conan-test" ^
     -e CONAN_BUILD_TESTING=1 ^
    --build=stsff-semver ^
    --build=outdated
    
call conan create . stsff/develop ^
     -s compiler="Visual Studio" ^
     -s compiler.version=15 ^
     -s compiler.runtime=MDd ^
     -s build_type=Debug ^
     -o stsff-semver:shared=True ^
     -e CONAN_TESTING_REPORT_DIR="report/conan-test" ^
     -e CONAN_BUILD_TESTING=1 ^
    --build=sts-semver ^
    --build=outdated

pause
:: remove build dir
rd /s/q "test_package/build"
```


##### Windows (.bat) building with the conan package tools
``` batch
::==========================================================
:: conan user userName -r remote -p password
::==========================================================
:: https://github.com/conan-io/conan-package-tools

set CONAN_USERNAME=steptosky
set CONAN_CHANNEL=testing
set CONAN_BUILD_TESTING=1
set CONAN_BUILD_POLICY=missing
set CONAN_VISUAL_VERSIONS=15
set CTEST_OUTPUT_ON_FAILURE=1

call python build.py

:: uncomment it if you want to
:: remove all packages from all versions 
:: from testing channel
conan remove sts-semver/*@steptosky/testing -f

pause

:: remove build dir
rd /s/q "test_package/build"
```

##### Unix (.sh) building with the conan package tools
``` bash
#==========================================================
# conan user userName -r remote -p password
#==========================================================
# https://github.com/conan-io/conan-package-tools

export CONAN_USERNAME=steptosky
export CONAN_CHANNEL=testing
export CONAN_BUILD_TESTING=1
export CONAN_BUILD_POLICY=missing
export CONAN_VISUAL_VERSIONS=15
export CTEST_OUTPUT_ON_FAILURE=1

python build.py

# uncomment it if you want to
# remove all packages from all versions 
# from testing channel
conan remove sts-semver/*@steptosky/testing -f

# remove build dir
rm -rf "test_package/build"
```

---

## For the library developers
- [release-checklist](release-checklist.md) see this file when you are making the release.
- [changelog](changelog.md) this file has to be filled during the release process and contains information about changes.
- [conan-package-tools](https://github.com/conan-io/conan-package-tools).
- [lasote docker hub](https://hub.docker.com/u/lasote/).

---


## Copyright
Copyright (c) 2018, StepToSky team. All rights reserved.  
[www.steptosky.com](http://www.steptosky.com/)