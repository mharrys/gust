Import('env')

cpppath = ['lib', 'src']
source = [Glob('src/*.cpp'), Glob('lib/lodepng/*.cpp')]
libs = ['assimp']

platform = ARGUMENTS.get('platform', 'desktop')
if platform == 'desktop':
    cpppath += ['src/platform/desktop']
    source += Glob(cpppath[-1] + '/*.cpp')
    libs += ['GL', 'GLEW']
    env.ParseConfig('sdl2-config --cflags --libs')
else:
    Exit('error: Unsupported platform "%s"' % platform)

env.Append(CPPPATH=cpppath)
env.Append(LIBS=libs)

env.Library('build/gust', source);
