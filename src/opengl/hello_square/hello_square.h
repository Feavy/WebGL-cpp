#pragma once

#include "../example/example.h"

class HelloSquare : public Example {
private:
    unsigned int _VBO, _EBO;
public:
    HelloSquare();
    void init();
    void draw(float dt) const;
};