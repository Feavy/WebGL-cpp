#pragma once

#include "../example/example.h"

class TextureTriangle : public Example {
private:
    unsigned int _texture1, _texture2;
public:
    TextureTriangle();
    void init();
    void draw(float dt) const;
};