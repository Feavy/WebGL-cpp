cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(emtest)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist)
set(CMAKE_RUNTIME_OUTPUT_NAME main.js)

# include_directories("lib/assimp/include")

# link_directories("lib/assimp/lib-js")
# link_libraries("assimp")

file(GLOB_RECURSE CORE_HDR src/*.h)
file(GLOB_RECURSE CORE_SRC src/*.cpp)

#
# Trying usual cmake project compiler execution
#

add_definitions("-std=c++17")
add_executable(main ${CORE_SRC} ${CORE_HDR})

set_target_properties(main PROPERTIES LINK_FLAGS "-s ASYNCIFY=1 -s EXPORTED_FUNCTIONS=_main,_hello,_newFrame -s ASYNCIFY_IMPORTS=load_image,flip_image_vertically --pre-js ${CMAKE_SOURCE_DIR}/pre.js --js-library ${CMAKE_SOURCE_DIR}/library.js")
