#include "rotating_triangle.h"

RotatingTriangle::RotatingTriangle() : Example() {
    
}


void RotatingTriangle::init() {

    ////////////////////////////////////////////////
    //
    //  DEFINITION DU SHADER
    //


    char *vertexData;
    char *fragmentData;
    int error, size;


    emscripten_wget_data("/assets/shaders/rotating_triangle/vertex.vs", (void **)&vertexData, &size, &error);
    emscripten_wget_data("/assets/shaders/rotating_triangle/fragment.fs", (void **)&fragmentData, &size, &error);

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
        printf("Vertex shader %s compiled successfully!\n", "/assets/shaders/rotating_triangle/vertex.vs");
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
        printf("Fragment shader %s compiled successfully!\n", "/assets/shaders/rotating_triangle/fragment.vs");
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
        -3*M_PI/4,  // bottom left
          -M_PI/4,  // bottom right
           M_PI/2   // top
    };

    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 

    rotationLocation = glGetUniformLocation(programID, "rotation");
}

void RotatingTriangle::draw(float dt) {
    rotation += M_PI*2 / 120.0 * ((1000.0/60.0) / dt);

    /*
    Pourquoi (1000.0/60.0) / dt ?

    On veut une vitesse de rotation constante quel que soit le taux de rafraichissement de l'écran.
    Avec un taux de rafraichissement de 60 fps on a un delta moyen de 1000/60 = 16.67 ms
    (1000.0/60.0) / dt vaut donc 1 sur un écran à 60fps
    et 0.5 sur un écran 120 fps -> à chaque frame on incrémente l'angle d'une valeur deux fois moins grande.
    */

    // Max : un tour complet : 360° : PI * 2

    if(rotation >= M_PI*2) {
        rotation -= M_PI*2;
    }

    glUniform1f(rotationLocation, rotation);

    glUseProgram(programID);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}