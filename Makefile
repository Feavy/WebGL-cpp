CC = emcc
CFLAGS = -O3 -w -D__linux__ -lm -s EXPORTED_FUNCTIONS=_main,_hello --js-library library.js
SRC = $(wildcard *.cpp */*.cpp */*/*.cpp */*/*/*.cpp)

all : $(SRC)
		@echo Building $^
		$(CC) $(CFLAGS) $^ -o dist/main.js
