#include "shader.h"

#include "opengl.h"


Shader::Shader(const char *vertexPath, const char *fragmentPath, std::map<int, std::string> attribLocations) {
    char *vertexData;
    char *fragmentData;
    int error, size;

    emscripten_wget_data(vertexPath, (void **)&vertexData, &size, &error);
    emscripten_wget_data(fragmentPath, (void **)&fragmentData, &size, &error);
    // Ou api fetch ?
    // Ou emscripten_async_wget_data ?

    // Free !

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
        printf("Vertex shader %s compiled successfully!\n", vertexPath);
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
        printf("Fragment shader %s compiled successfully!\n", fragmentPath);
    }

    // Program

    ID = glCreateProgram();

    printf("Created Shader ID %d\n", ID);

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    for (auto const &[key, val] : attribLocations) {
        glBindAttribLocation(ID, key, val.c_str());
    }
    // Bind vPosition to attribute 0
    // glBindAttribLocation(ID, 0, "vPosition");
    // Bind aColor to attribute 0
    // glBindAttribLocation(ID, 1, "aColor");

    // Note : autre possibilit√© avec glGetAttribLocation
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


    // Free !
    free(vertexData);
    free(fragmentData);
}

bool Shader::loaded() {
    return _loaded;
}

void Shader::use() const{
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