import os

gmock_dir = os.environ.get('GMOCK_DIR')
gtest_dir = os.environ.get('GTEST_DIR')

gmock_lib = os.path.join(gmock_dir, 'build')
gmock_inc = os.path.join(gmock_dir, 'include')
gtest_inc = os.path.join(gtest_dir, 'include')

env = Environment(
    CC='g++',
    CCFLAGS='-std=c++11 -pedantic -Wall -Wextra -O3',
    CPPPATH=['lib', 'src', 'test', gmock_inc, gtest_inc],
    LIBPATH=[gmock_lib],
    LIBS=['gmock', 'pthread'],
)

source = []
source += Glob('test/*.cpp')
# for now, only add specific files until platform specific code is mocked
source += ['src/annotationarray.cpp']
source += ['src/annotationbasic.cpp']
source += ['src/annotationstruct.cpp']
source += ['src/shadoweddataimpl.cpp']
source += ['src/worldrunner.cpp']

program = env.Program(target='bin/run_all_tests', source=source);
