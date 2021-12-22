#include "hello_square.h"

#include "../opengl.h"

HelloSquare::HelloSquare() : Example(
    {
        "/assets/basic_shader/vertex.vs",
        "/assets/basic_shader/fragment.fs",
        {
            {0, "vPosition"},
            {1, "aColor"}
        }
    }
) {

}

void HelloSquare::init() {

    unsigned short indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    float vertices[] = {
        // position  // color
        0, 0, 0, /**/ 0, 0, 0,    // top left
        0, 0, 0, /**/ 0, 0, 0,    // top right
        0, 0, 0, /**/ 0, 0, 0,    // bottom right
        0, 0, 0, /**/ 0, 0, 0};   // bottom left

    // Vertex buffer object
    glGenBuffers(1, &_VBO);
    // Element buffer object
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    

    glGenBuffers(1, &_EBO);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    // GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    // GL_STATIC_DRAW: the data is set only once and used many times.
    // GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

}

void HelloSquare::draw(float dt) const {
    // OpenGL ES 2.0

    // Dessin du carré

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

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    // Element buffer object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

    // float greenValue = (sin(elapsed / 1000.f) / 2.0f) + 0.5f;

    getShader().use();
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