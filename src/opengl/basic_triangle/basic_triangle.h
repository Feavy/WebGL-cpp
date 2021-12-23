#pragma once

#include "../example/example.h"

class BasicTriangle : public Example {
private:
    unsigned int programID, _VBO, _EBO;
public:
    BasicTriangle();
    void init();
    void draw(float dt) const;
};