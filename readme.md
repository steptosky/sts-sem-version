# Cross-platform header only C++ library for working with Semantic Versioning.


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
  [bintray](https://bintray.com/steptosky/conan-open-source/sts-semver:steptosky) remote without pre-built packages.  
  ```sts-semver/X.Y.Z@steptosky/stable```  

#### warning 
- As the library hasn't got the major version 
  the library's interface and logic aren't stable and can be changed at any time.

---

## Build

#### dependencies
- [Cmake 3.7+](https://cmake.org) - build tool.
- [Conan 1.3+](https://www.conan.io) - dependency tool.
- [Python 2 or 3](https://www.python.org) - is needed for the Conan.
- [Doxygen](http://www.stack.nl/~dimitri/doxygen) - if you want to generate the documentation.
- [Gtest and Gmock 1.8](https://github.com/google/googletest) - testing (used through the Conan)  

#### documentation
Run from the root folder ``` doxygen doxyfile ``` the result will be in the _doc-generated_ folder.  
The _doxygen_ has to be accessible through your PATH environment variable.

#### conan evironment variables
- _CONAN_TEST_REPORT_DIR_=(string path) - A path for storing tests results. Default value is specified in the cmake script.
- _CONAN_TEST_LIB_=(0 or 1) - Enables/disables building and running the tests.  
  If you set BUILD_TESTS=ON as a parameter while running ```cmake``` command it will auto-set _CONAN_TEST_LIB_ variable to "1".

#### cmake variables
- _BUILD_TESTS=(ON/OFF)_ - Enable or disable building the test projects.
- _TEST_REPORT_DIR_=(string path) - You can specify the directory for the tests reports, it is useful for CI.

Sometimes you will need to delete the file _cmake/conan.cmake_ then the newer version of this file will be downloaded from the Internet while running ```cmake``` command.  
This file is responsible for cmake and conan interaction.

#### Build scripts examples:
These scripts are just examples!  
Probably you will need to adjust them for your purposes.

##### Windows (.bat) For Visual Studio 2017 x64
```
::==========================================================
@echo off
:: Fix problems with some symbols
REM change CHCP to UTF-8
CHCP 1252
CLS
::==========================================================
::conan user userName -r remote -p password
::==========================================================
set dir="msvc"
if not exist %dir% mkdir %dir%
cd %dir%
::==========================================================
call cmake -G "Visual Studio 15 Win64" ../ ^
    -DCMAKE_INSTALL_PREFIX=../output ^
    -DBUILD_TESTS=ON
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
```
#===========================================================
dir_name="build-release"
#===========================================================
rm -r ${dir_name}
mkdir ${dir_name}
cd ${dir_name}
#===========================================================
#conan user userName -r remote -p password
#===========================================================
cmake -G"Unix Makefiles" ../ \
    -DCMAKE_BUILD_TYPE="Release" \
    -DCMAKE_INSTALL_PREFIX=../output \
    -DBUILD_TESTS=ON
cmake --build . --target install
cd ../
#===========================================================
```

##### Mac OS (.sh)
```
#===========================================================
dir_name="build-release"
#===========================================================
rm -r ${dir_name}
mkdir ${dir_name}
cd ${dir_name}
#===========================================================
#conan user userName -r remote -p password
#===========================================================
cmake -G"Unix Makefiles" ../ \
    -DCMAKE_BUILD_TYPE="Release" \
    -DCMAKE_INSTALL_PREFIX=../output \
    -DBUILD_TESTS=ON
cmake --build . --target install
cd ../
#===========================================================
```


#### Build with the conan 'create' script example:
This is just the example for the windows!  
Probably you will need to adjust it for your purposes.
##### Windows (.bat) For Visual Studio 2017 x64
```
::call conan user userName -r remote -p password
conan create . steptosky/develop ^
     -s compiler="Visual Studio" ^
     -s compiler.version=15 ^
     -s compiler.runtime=MD ^
     -s build_type=Release ^
     -e CONAN_TEST_REPORT_DIR="report/conan-test" ^
     -e CONAN_TEST_LIB=1
     
conan create . steptosky/develop ^
     -s compiler="Visual Studio" ^
     -s compiler.version=15 ^
     -s compiler.runtime=MDd ^
     -s build_type=Debug ^
     -e CONAN_TEST_REPORT_DIR="report/conan-test" ^
     -e CONAN_TEST_LIB=1
     

pause
:: remove build dir
rd /s/q "test_package/build"
```
After building the package will be available in the conan local cache,
so you can use it in your other projects on local PC.  

---

## For the library developers
- [release-checklist](release-checklist.md) If you are making the release.
- [changelog](changelog.md) - this file is filling during the release process or when a feature is added.
- [conan-package-tools](https://github.com/conan-io/conan-package-tools)
- [lasote docker hub](https://hub.docker.com/u/lasote/)
---


## Copyright
Copyright (c) 2018, StepToSky team. All rights reserved.  
[www.steptosky.com](http://www.steptosky.com/)