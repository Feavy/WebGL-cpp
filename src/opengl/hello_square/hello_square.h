#pragma once

#include "../example/example.h"

class HelloSquare : public Example {
public:
    HelloSquare();
    void init();
    void draw(float dt) const;
};