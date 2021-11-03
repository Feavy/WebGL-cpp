#pragma once

#include <cmath>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <memory>
#include <string>
#include <webgl/webgl1.h>
#include "shader.h"
#include "./example/example.h"

extern float elapsed;

typedef unsigned int image_t;

class OpenGLExampleRunner {
private:
    Example* _example;
    OpenGLExampleRunner();
public:
    static OpenGLExampleRunner INSTANCE;
    void setup() const;
    void run(Example* example);
    void draw(float dt);
};

extern "C" {
void glTexImage2D_external(GLenum target, GLint level, GLint internalformat, GLenum format, GLenum type, image_t image);
image_t load_image(const char* path);
void flip_image_vertically(image_t image);
}

void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLenum format, GLenum type, image_t image);