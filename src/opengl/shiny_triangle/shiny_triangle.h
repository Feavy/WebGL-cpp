#pragma once

#include "../opengl.h"
#include "../example/example.h"

class ShinyTriangle : public Example {
private:
    unsigned int programID, _VBO;
    int colorLocation;
public:
    ShinyTriangle();
    void init();
    void draw(float dt);
};