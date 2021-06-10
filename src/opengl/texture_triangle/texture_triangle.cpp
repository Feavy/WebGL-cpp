#include "texture_triangle.h"

#include "../opengl.h"

unsigned int texture1, texture2;

void opengl_init() {
    myVertexShader = {"/assets/texture_shader/vertex.vs", "/assets/texture_shader/fragment.fs", {{0, "vPosition"}, {1, "aColor"}, {2, "aTexCoord"}}};

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glGenerateMipmaps

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    image_t img = load_image("/assets/textures/container.jpg");
    printf("/assets/textures/wall.jpg -> %d\n", img);
    if (img) {
        // target  mipmapLvl internalFormat imageFormat type image
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, img);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        emscripten_console_error("Could not load texture /assets/textures/wall.jpg");
    }

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    img = load_image("/assets/textures/awesomeface.png");
    printf("/assets/textures/awesomeface.png -> %d\n", img);
    if (img) {
        // target  mipmapLvl internalFormat imageFormat type image
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, img);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        emscripten_console_error("Could not load texture /assets/textures/awesomeface.jpg");
    }

    myVertexShader.use();
    myVertexShader.setInt("texture1", 0); // GL_TEXTURE0
    myVertexShader.setInt("texture2", 1); // GL_TEXTURE0

    // free image memory ? --> supprimer le HTMLImageElement de l'array images ?

    // emscripten_glTexImage2D(0, 0, 0, 0, 0, 0, 0, 0, (void *)0);
}

void opengl_draw(float dt) {

    const float vertices[] = {
        // positions // colors // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
    };

    unsigned short indices[] = {
        0, 1, 3,
        1, 2, 3};


    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Element buffer object
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    myVertexShader.use();

    glActiveTexture(GL_TEXTURE0); // Optionnel (GL_TEXTURE0 activée par defaut)
    glBindTexture(GL_TEXTURE_2D, texture1);

    glActiveTexture(GL_TEXTURE1); 
    glBindTexture(GL_TEXTURE_2D, texture2);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}