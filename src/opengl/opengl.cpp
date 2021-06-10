#include "opengl.h"

float elapsed = 0;

void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLenum format, GLenum type, image_t image) {
    glTexImage2D_external(target, level, internalformat, format, type, image);
}

void opengl() {
    printf("[opengl]\n");
    EmscriptenWebGLContextAttributes config{stencil : GL_TRUE, antialias : GL_TRUE};

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = emscripten_webgl_create_context("canvas", &config);
    emscripten_webgl_make_context_current(context);
    emscripten_console_log("Context created");

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

    // Attention -> Différence de syntaxe des shaders GL2 / GL3

    // Utilisation de varying [<precision>p] vec4 <var>; pour passer des vec d'un shader à l'autre
    // Exemple : varying highp vec4 vertexColor;

    opengl_init();
    myVertexShader.use();

    EM_ASM({
        var i = 0;
        var lastTime = 0;
        function step(timestamp) {
            var dt = timestamp - lastTime;
            lastTime = timestamp;
            Module._newFrame(dt);
            requestAnimationFrame(step);
        }
        function prestep(timestamp) {
            lastTime = timestamp;
            requestAnimationFrame(step);
        }
        requestAnimationFrame(prestep);
    });
    printf("[opengl] Done.\n");
}

extern "C" {
void newFrame(float dt) {
    // printf("Draw called Delta=%f Total=%f\n", dt, elapsed);

    // TODO : voir partie 4.2 -> Viewport

    glClearColor(1, 1, 1, 1);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    
    if(!myVertexShader.loaded()) {
        return;
    }

    opengl_draw(dt);
    elapsed += dt;
}
}