#pragma once

#include "../shader.h"

class Example {
protected:
    Shader _shader;
public:
    Example(Shader shader);
    virtual void init() = 0;
    virtual void draw(float dt) const = 0;
    Shader getShader() const;
};