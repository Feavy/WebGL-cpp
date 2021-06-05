#include <emscripten/html5.h>
#include <webgl/webgl1.h>

void render() {
    // OpenGL ES 2.0

    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = emscripten_webgl_create_context("canvas", nullptr);
    emscripten_webgl_make_context_current(context);
    emscripten_console_log("Context created");
}