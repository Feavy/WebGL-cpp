#pragma once

#include <cmath>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <memory>
#include <string>
#include <webgl/webgl1.h>
#include "shader.h"

extern float elapsed;
extern Shader myVertexShader;

typedef unsigned int image_t;

void opengl();
extern void opengl_init();
extern void opengl_draw(float dt);


extern "C" {
void glTexImage2D_external(GLenum target, GLint level, GLint internalformat, GLenum format, GLenum type, image_t image);
image_t load_image(const char* path);
}

void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLenum format, GLenum type, image_t image);