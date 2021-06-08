#include "opengl.h"

float elapsed = 0;

void opengl_init() {
    printf("[opengl_init]\n");
    EmscriptenWebGLContextAttributes config{stencil : GL_TRUE, antialias : GL_TRUE};

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = emscripten_webgl_create_context("canvas", &config);
    emscripten_webgl_make_context_current(context);
    emscripten_console_log("Context created");

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

    // Attention -> Différence de syntaxe des shaders GL2 / GL3

    // Utilisation de varying [<precision>p] vec4 <var>; pour passer des vec d'un shader à l'autre
    // Exemple : varying highp vec4 vertexColor;

    myVertexShader.use();

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

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
    printf("[opengl_init] Done.\n");
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