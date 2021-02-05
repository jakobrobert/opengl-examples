# OpenGL Examples
OpenGL examples implemented in C++ using CMake as the build system.

## Clone
The repository makes use of submodules. Therefore, you should clone it with the `--recursive` option:
```
git clone --recursive https://github.com/jakobrobert/opengl-examples.git
```

If you already cloned it before without the `--recursive` option, use the following command to clone the submodules:
```
git submodule update --init
```

## Build and Run (Linux)
So far, the project has only been tested under Linux Debian.

In order to build, you need to install the CMake build tool, g++ compiler and the X11 packages:
```
sudo apt-get install g++
sudo apt-get install cmake
sudo apt-get xorg-dev
```

You can then build all examples by executing the build script:
```
./build.sh
```

To clean the build directory, execute the clean script:
```
./clean.sh
```

Each example has its own sub-directory in the directory `build/examples`.
To execute any example, you first need to change the directory.
E.g to execute the first example, execute the following commands starting from the root of the project.
```
cd build/examples/01-window
./01-window
```
