# WebGL C++
Project to test WebGL rendering using C++ (compiled to WASM thank to Emscripten).

## Installation

1. Install Make https://github.com/vlang/v/wiki/Installing-a-C-compiler-on-Windows#1-mingw-w64
2. Copy mingw32-make.exe to make.exe and add bin folder to path
3. Install emsdk https://emscripten.org/docs/getting_started/downloads.html#installation-instructions-using-the-emsdk-recommended
4. Add emsdk to path
5. Install C/C++ Intellisense VS Code extension
6. Update settings C_Cpp.default.includePath = "...\emsdk\upstream\emscripten\cache\sysroot\include"
7.

```bash
cd build
# edit gen file with a valid path to Emscripten.cmake
./gen
make
```