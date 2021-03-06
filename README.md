Gust
====
3D rendering engine created for fun to explore topics in real-time computer
graphics.

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

### [Billboarding](https://github.com/mharrys/billboarding)

![billboarding](https://github.com/mharrys/billboarding/raw/master/scrot.png)

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
In order to run the tests you need to have gmock setup on your system. For
example, download and compile gmock and place the libraries in
`/usr/local/lib{64}/` and include directories in `/usr/local/include/`.

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
