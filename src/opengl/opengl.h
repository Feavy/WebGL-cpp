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

void opengl_init();
extern void opengl_draw(float dt);