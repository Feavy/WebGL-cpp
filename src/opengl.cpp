#include <emscripten.h>
#include <emscripten/html5.h>
#include <memory>
#include <string>
#include <webgl/webgl1.h>

unsigned int loadShader(unsigned int shaderType, const char *source);
unsigned int loadProgram(unsigned int vertexShader, unsigned int fragmentShader);

unsigned int shaderProgram;

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

    const char *vertexShaderSource = "attribute vec4 vPosition;                 \n"
                                     "varying mediump vec4 vertexColor;         \n"
                                     "void main()                               \n"
                                     "{                                         \n"
                                     "   gl_Position = vPosition;               \n"
                                     "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
                                     "}                                         \n";

    unsigned int vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource);

    const char *fragmentShaderSource = "precision mediump float;                \n"
                                       "varying mediump vec4 vertexColor;       \n"
                                       "uniform vec4 ourColor;                  \n"
                                       "void main()                             \n"
                                       "{                                       \n"
                                       "  gl_FragColor = ourColor;              \n"
                                       "}                                       \n";

    unsigned int fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    shaderProgram = loadProgram(vertexShader, fragmentShader);

    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    EM_ASM({
        var i = 0;
        var lastTime = 0;
        function step(timestamp) {
            var dt = timestamp - lastTime;
            lastTime = timestamp;
            Module._newFrame(dt);
            if (i++ < 60 * 10) {
                requestAnimationFrame(step);
            }
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

    // Dessin du triangle

    float transformVal = (sin(elapsed / 1000.f) / 2.0f) + 0.5f;

    float vertices[] = {
        -0.5f, 0.5f, 0.0f,                   // top left
        transformVal, transformVal, 0.0f,    // top right
        0.5f, -0.5f, 0.0f,                   // bottom right
        -transformVal, -transformVal, 0.0f}; // bottom left

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

    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUseProgram(shaderProgram);
    glUniform4f(vertexColorLocation, 0.0f, transformVal, 1 - transformVal, 1.0f);

    // Note : VAO uniquement dispo en WebGL2 (77% de coverage browers)

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(0);

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

unsigned int loadShader(unsigned int shaderType, const char *source) {
    unsigned int shader = glCreateShader(shaderType);

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::%d::COMPILATION_FAILED\n%s\n", shaderType, infoLog);
    } else {
        printf("Vertex shader compiled successfully!\n");
    }
    return shader;
}

unsigned int loadProgram(unsigned int vertexShader, unsigned int fragmentShader) {
    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Bind vPosition to attribute 0
    glBindAttribLocation(shaderProgram, 0, "vPosition");

    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::PROGRAM::LINK_FAILED\n%s\n", infoLog);
    } else {
        printf("Program linked successfully!\n");
    }
    return shaderProgram;
}