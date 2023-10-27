# optparse

An applicative CLI option parser ported from the Haskell equivalent
[https://github.com/pcapriotti/optparse-applicative](https://github.com/pcapriotti/optparse-applicative).

## Test

To build, and run the tests use the following commands.

```bash
cmake -B build -S . -DBUILD_TESTING=On
cmake --build build
ctest --test-dir build/ --rerun-failed --output-on-failure
```
