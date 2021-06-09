#include "texture_triangle.h"

#include "../opengl.h"

void opengl_init() {
    myVertexShader = {"/assets/basic_shader/vertex.vs", "/assets/basic_shader/fragment.fs", {{0, "vPosition"}, {1, "aColor"}}};

    image_t img = load_image("/assets/textures/wall.jpg");
    printf("/assets/textures/wall.jpg -> %d\n", img);

    glTexImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, img);
    // emscripten_glTexImage2D(0, 0, 0, 0, 0, 0, 0, 0, (void *)0);
}

void opengl_draw(float dt) {
    const float texCoords[] = {
        0.f, 0.f,
        1.f, 0.f,
        0.5f, 1.f};

    const float vertices[] = {
        -0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f,
        0.f, 0.5f, 0.f, 0.f, 0.f, 1.f,
        0.5f, -0.5f, 0.f, 0.f, 1.f, 0.f};

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // // glGenerateMipmaps

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    myVertexShader.use();

    glDrawArrays(GL_TRIANGLES, 0, 3);
}