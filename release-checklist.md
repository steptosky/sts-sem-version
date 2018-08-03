## Release checklist
- Check whether the [change log](changelog.md) is correct.
- Check whether the `doxygen` does not have unexpected warnings and errors while generating the documentation.  
  It may have warning if the project was generated as shared on windows.
- Check whether the dependencies and their version are described correctly in the [readme.md](readme.md) file. 

#### [StsProjectDesc.cmake](cmake/StsProjectDesc.cmake)
- Set the correct version in the file and check other information there.
- Check whether `ProjectVersionSnapshot` has the correct value for your branch.
  It should be `ON` for unstable branches like `feature, develop ...` and `OFF` for stable `master, release ...`.

#### [conanfile.py](conanfile.py)
- Set the correct version.
- Check whether the file uses the correct dependencies and their version.
- Check whether the conan ```test_package``` works correctly.
