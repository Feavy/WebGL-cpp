CC = emcc
CFLAGS = -g -s ASYNCIFY=1 -w -D__linux__ -lm -s EXPORTED_FUNCTIONS=_main,_hello,_newFrame -s ASYNCIFY_IMPORTS=load_image,flip_image_vertically --pre-js pre.js --js-library library.js
SRC = $(wildcard *.cpp */*.cpp */*/*.cpp src/opengl/example/*.cpp src/opengl/texture_triangle/*.cpp)

all : $(SRC)
		@echo Building $^
		$(CC) $(CFLAGS) $^ -o dist/main.js
