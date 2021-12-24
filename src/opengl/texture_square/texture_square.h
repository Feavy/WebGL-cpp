#pragma once

#include "../example/example.h"

class TextureSquare : public Example {
private:
    unsigned int _texture1, _texture2, _VBO, _EBO;
public:
    TextureSquare();
    void init();
    void draw(float dt);
};