# The command line option parser `optparse`

An applicative command line option (CLI) parser based on the Haskell library
[optparse-applicative](https://github.com/pcapriotti/optparse-applicative).

## Build and run the tests

To build, and run the tests use the following commands.

```bash
cmake -B build -S . -DBUILD_TESTING=On
cmake --build build --target optparse-test
ctest --test-dir build/ --rerun-failed --output-on-failure
```

## Build the Doxygen documentation

To build the Doxygen documentation run the following commands.

```bash
cmake -B build -S . -DBUILD_DOCUMENTATION=On
cmake --build build --target doxygen
ctest --test-dir build/ --rerun-failed --output-on-failure
```

## License

Please have a look at the [license file](LICENSE.md).
