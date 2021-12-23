#pragma once

#include "../example/example.h"

class AnimatedSquare : public Example {
private:
    unsigned int _VBO, _EBO;
public:
    AnimatedSquare();
    void init();
    void draw(float dt) const;
};