#include <emscripten/html5.h>
#include <memory>
#include <string>
#include <webgl/webgl1.h>

unsigned int loadShader(unsigned int shaderType, const char *source);
unsigned int loadProgram(unsigned int vertexShader, unsigned int fragmentShader);

void render_test() {
    EmscriptenWebGLContextAttributes config{stencil : GL_TRUE, antialias : GL_TRUE};

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = emscripten_webgl_create_context("canvas", &config);
    emscripten_webgl_make_context_current(context);
    emscripten_console_log("Context created");

    // TODO : voir partie 4.2 -> Viewport

    // OpenGL ES 2.0

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Dessin du triangle

    float vertices[] = {
        -0.5f, 0.5f, 0.0f,   // top left
        0.5f, 0.5f, 0.0f,    // top right
        0.5f, -0.5f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f}; // bottom left

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

    // Attention -> Différence de syntaxe des shaders GL2 / GL3

    const char *vertexShaderSource = "attribute vec4 vPosition;    \n"
                                     "void main()                  \n"
                                     "{                            \n"
                                     "   gl_Position = vPosition;  \n"
                                     "}                            \n";

    unsigned int vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource);

    const char *fragmentShaderSource = "precision mediump float;\n"
                                       "void main()                                  \n"
                                       "{                                            \n"
                                       "  gl_FragColor = vec4 ( 1.0, 0.5, 0.2, 1.0 );\n"
                                       "}                                            \n";

    unsigned int fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    unsigned int shaderProgram = loadProgram(vertexShader, fragmentShader);

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Note : VAO uniquement dispo en WebGL2 (77% de coverage browers)

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(0);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
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