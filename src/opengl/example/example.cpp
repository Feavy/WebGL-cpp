#include "example.h"

Example::Example(Shader shader) : _shader{shader} {

}

Shader Example::getShader() const {
    return _shader;
}