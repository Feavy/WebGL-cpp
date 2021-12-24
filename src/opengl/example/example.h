#pragma once

#include "../shader.h"
#include <memory>

class Example {
protected:
    std::unique_ptr<Shader> _shader;
public:
    Example(Shader shader);
    Example();
    virtual void init() = 0;
    virtual void draw(float dt) = 0;
};