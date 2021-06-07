#include "opengl.h"

Shader myVertexShader{"/assets/basic_shader/vertex.vs", "/assets/basic_shader/fragment.fs"};

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

float elapsed;

void opengl_draw(float dt) {
    // OpenGL ES 2.0

    // TODO : voir partie 4.2 -> Viewport

    glClearColor(1, 1, 1, 1);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    
    if(!myVertexShader.loaded()) {
        return;
    }

    // Dessin du triangle

    float transformVal = (sin(elapsed / 1000.f) / 2.0f) + 0.5f;

    float vertices[] = {
        // position  // color
        -0.5f, 0.5f, 0.0f, /**/ 0.f, 1-transformVal, transformVal,                   // top left
        transformVal, transformVal, 0.0f, /**/ 0.f, transformVal, 1-transformVal,    // top right
        0.5f, -0.5f, 0.0f, /**/ transformVal, 0.f, 0.f,                   // bottom right
        -transformVal, -transformVal, 0.0f, /**/ 1-transformVal, transformVal, transformVal}; // bottom left
    /*
    Autre possibilité : faire un second tableau pour les couleurs
    et utiliser un système analogue au tableau vertices pour y accéder depuis le shader
    https://github.com/bonigarcia/webgl-examples/blob/master/basic_concepts/colored-triangle.html
    */

    unsigned short indices[] = {
        0, 1, 3,
        1, 2, 3};

    // Vertex buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Element buffer object
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    // GL_STATIC_DRAW: the data is set only once and used many times.
    // GL_DYNAMIC_DRAW: the data is changed a lot and used many times.

    float greenValue = (sin(elapsed / 1000.f) / 2.0f) + 0.5f;

    myVertexShader.use();
    // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    // glUseProgram(shaderProgram);
    // glUniform4f(vertexColorLocation, 0.0f, transformVal, 1 - transformVal, 1.0f);

    // Note : VAO uniquement dispo en WebGL2 (77% de coverage browers)

    // Ou utiliser getAttribLocation
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    // Wireframe : GL_LINE_LOOP

    // glDrawArrays(GL_TRIANGLES, 0, 3);
}

extern "C" {
void newFrame(float dt) {
    // printf("Draw called Delta=%f Total=%f\n", dt, elapsed);
    opengl_draw(dt);
    elapsed += dt;
}
}