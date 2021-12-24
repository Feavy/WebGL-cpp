#pragma once

#include "../opengl.h"
#include "../example/example.h"

class RotatingTriangle : public Example {
private:
    unsigned int programID, _VBO;
    int rotationLocation;
    float rotation;
public:
    RotatingTriangle();
    void init();
    void draw(float dt);
};