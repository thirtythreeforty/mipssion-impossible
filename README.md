This is a microarchitecture-level emulator for the MIPSsion Impossible processor, a MIPS-style 16-bit processor.

## Cloning
Make sure you get the Google Tests submodule as well by using `git clone --recursive`, or you'll get an error when you try to build.
Alternatively, if you've already cloned the repository, you can use `git submodule update --init` to clone the submodule.

## Compiling
To build, you'll need to ensure you have CMake 3.5 or better installed.
You also need a relatively recent compiler, one that has support for C++14, such as GCC 5.x or Visual Studio 2015.

Aim CMake at the main `CMakeLists.txt` file in this top directory and generate the relevant build files for your compiler.
On Linux, this process would look like this:

    mkdir build && cd build/
    cmake .. -DCMAKE_BUILD_TYPE=Debug

On Windows, you could use the CMake GUI and instead generate Visual Studio project files.

Now you should be ready to build!

## Structure
The project is currently organized into three main modules: `libmiemu`, the MI emulator library that does all the work, a `miemu` command-line wrapper, and a test framework using Google Tests.
After you build, you can run `miemu` from the build directory.
The test binary will be at `build/tests/mitests`; running it will run all unit tests.

## Resources
- [Google Tests introduction](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md)
- [CMake tutorial](https://cmake.org/cmake-tutorial/)
