#pragma once

#include "../example/example.h"

class BasicSquare : public Example {
private:
    unsigned int programID, _VBO, _EBO;
public:
    BasicSquare();
    void init();
    void draw(float dt) const;
};