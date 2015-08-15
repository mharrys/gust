import os

env = Environment(
    CC='g++',
    CCFLAGS='-std=c++11 -pedantic -Wall -Wextra -O3',
    CPPPATH=['lib', 'src', 'test'],
    LIBS=['gmock', 'pthread'],
)

source = []
source += Glob('test/*.cpp')
# for now, only add specific files until platform specific code is mocked
source += ['src/annotationarray.cpp']
source += ['src/annotationfree.cpp']
source += ['src/annotationstruct.cpp']
source += ['src/shadoweddataimpl.cpp']
source += ['src/worldrunner.cpp']

program = env.Program(target='bin/run_all_tests', source=source);
