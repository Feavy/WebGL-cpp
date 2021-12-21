# https://github.com/emscripten-core/emscripten/tree/main/tests/cmake

cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(webglcpp)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist)


file(GLOB_RECURSE CORE_HDR src/*.h)
file(GLOB_RECURSE CORE_SRC src/*.cpp)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Or :
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")


# Enable Asyncify
set(linkFlags "-s ASYNCIFY=1")

# List exported functions
set(linkFlags "${linkFlags} -s EXPORTED_FUNCTIONS=_main,_hello,_newFrame")

# List asyncify imports
set(linkFlags "${linkFlags} -s ASYNCIFY_IMPORTS=load_image,flip_image_vertically")


add_executable(main ${CORE_SRC} ${CORE_HDR})

set_target_properties(main PROPERTIES LINK_FLAGS "${linkFlags}")


em_link_pre_js(main "pre.js")
em_link_js_library(main "library.js")