# Tetris
A simple game of tetris using C++ and OpenGL.

Mainly inteded as a proof of concept for circular Model -> Engine -> Model architecture capable of supporting most of 2D and, probably, 3D scenes (with exception of scenes requiring network and/or database interaction) with minimal effort.  

## Use CMake to build
It's easy. Get [CMake](https://cmake.org/download/) for your platform, open it, and copy-past the path at which the copy of this project resides. Select a directory in which a project should be built, usually it's "..path-to-project/build", and hit 'generate'. This will put all of the sources, headers and libraries into a single project using compiler of your own liking. Now you just have to open that project and hit 'build'. 

You may play the game in your programming environment, or take the binaries from 'build/Debug'.

### Apologies 
Being what it is, the game isn't entirely finished, nor is it actually playable. In a week or so the following things should be changed:

* Architecture expansion, eliminating obvious technical flaws
* Game logic, completing all of the desired functions such as row elimination when it's complete
* Design, finally some proper shaders should be written, making it bright and fancy
