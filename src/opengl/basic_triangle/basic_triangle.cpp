#include "basic_triangle.h"

BasicTriangle::BasicTriangle() : Example() {
    
}


void BasicTriangle::init() {

    ////////////////////////////////////////////////
    //
    //  DEFINITION DU SHADER
    //


    char *vertexData;
    char *fragmentData;
    int error, size;


    emscripten_wget_data("/assets/shaders/basic_triangle/vertex.vs", (void **)&vertexData, &size, &error);
    emscripten_wget_data("/assets/shaders/basic_triangle/fragment.fs", (void **)&fragmentData, &size, &error);

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
        printf("Vertex shader %s compiled successfully!\n", "/assets/shaders/basic_triangle/vertex.vs");
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
        printf("Fragment shader %s compiled successfully!\n", "/assets/shaders/basic_triangle/fragment.vs");
    }

    // Program

    programID = glCreateProgram();

    printf("Created Shader ID %d\n", programID);

    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);

    glBindAttribLocation(programID, 0, "aPos");

    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        printf("ERROR::PROGRAM::LINK_FAILED\n%s\n", infoLog);
    } else {
        printf("Program linked successfully!\n");
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Free !
    free(vertexData);
    free(fragmentData);



    ////////////////////////////////////////////////
    //
    //  COMMENT INTERPRETER LES DONNEES DU BUFFER
    //

    float vertices[] = {
        -0.5, -0.5, 0.0,   // bas gauche
        0.5, -0.5,  0.0,   // bas droit
        0.0,  0.5,  0.0    // haut
    };

    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
}

void BasicTriangle::draw(float dt) const {
    glUseProgram(programID);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}