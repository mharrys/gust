Gust
====
3D rendering engine created for fun to explore topics in real-time computer
graphics.

Dependencies
============
This project uses [SCons](http://www.scons.org) as a software construction
tool. You will need a C++11 compiler, GLM, GLEW, AssImp and SDL2. Consult
SConscript for details.

Test
====
This project uses [Google C++ Testing Framework](https://code.google.com/p/googletest/) and
[Google C++ Mocking Framework](https://code.google.com/p/googlemock/) for
testing.

Setup
-----
Before you can run the tests you need to download and compile the testing
framework, when this is done you need to export the following two environment
variables.

    export GMOCK_DIR=/path/to/gmock/dir
    export GTEST_DIR=/path/to/gtest/dir

Run all tests
-------------

    $ scons
    $ cd bin
    $ ./run_all_tests

Run a specific test
-------------------

    $ scons
    $ cd bin
    $ ./run_all_tests --gtest_filter=WorldRunnerTest.*
    $ ./run_all_tests --gtest_filter=WorldRunnerTest.BreakControlIfWindowShouldClose

Examples
========
Following are projects that depends on this engine.

### [Arcball Rotation Control](https://github.com/mharrys/arcball)

![arcball](https://github.com/mharrys/arcball/raw/master/scrot.png)

### [Omnidirectional Shadow Mapping](https://github.com/mharrys/omni)

![omni](https://github.com/mharrys/omni/raw/master/scrot.png)

### [Bloom](https://github.com/mharrys/bloom)

![bloom](https://github.com/mharrys/bloom/raw/master/scrot.png)

### [Rim Lighting](https://github.com/mharrys/rim)

![rim](https://github.com/mharrys/rim/raw/master/scrot.png)
