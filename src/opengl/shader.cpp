#include "shader.h"

// emscripten_wget_data
typedef unsigned int image_t;

extern "C" {
void glTexImage2D_internal(GLenum target, GLint level, GLint internalformat, GLenum format, GLenum type, image_t image);
image_t load_image(const char* path);
}

void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLenum format, GLenum type, image_t image) {
    glTexImage2D_internal(target, level, internalformat, format, type, image);
}


Shader::Shader(const char *vertexPath, const char *fragmentPath, std::map<int, std::string> attribLocations) {
    char *vertexData;
    char *fragmentData;
    int error, size;

    emscripten_wget_data(vertexPath, (void **)&vertexData, &size, &error);
    emscripten_wget_data(fragmentPath, (void **)&fragmentData, &size, &error);
    // Ou api fetch ?
    // Ou emscripten_async_wget_data ?

    // Free !

    image_t img = load_image("/assets/textures/wall.jpg");
    printf("Received image : %d\n", img);

    // Vertex shader

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexData, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    } else {
        printf("Vertex shader compiled successfully!\n");
    }

    // Fragment shader

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentData, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    } else {
        printf("Fragment shader compiled successfully!\n");
    }

    // Program

    ID = glCreateProgram();

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    for (auto const &[key, val] : attribLocations) {
        glBindAttribLocation(ID, key, val.c_str());
    }
    // Bind vPosition to attribute 0
    // glBindAttribLocation(ID, 0, "vPosition");
    // Bind aColor to attribute 0
    // glBindAttribLocation(ID, 1, "aColor");

    // Note : autre possibilité avec glGetAttribLocation
    // https://github.com/bonigarcia/webgl-examples/blob/master/basic_concepts/draw-a-triangle.html

    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        printf("ERROR::PROGRAM::LINK_FAILED\n%s\n", infoLog);
    } else {
        printf("Program linked successfully!\n");
        _loaded = true;
    }

    int vertexColorLocation = glGetUniformLocation(ID, "ourColor");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glTexImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, img);
    emscripten_glTexImage2D(0, 0, 0, 0, 0, 0, 0, 0, (void *)0);

    // glTexImage2D()

    // Free !
    free(vertexData);
    free(fragmentData);
}

bool Shader::loaded() {
    return _loaded;
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}