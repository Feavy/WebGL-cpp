#include "example.h"

Example::Example(Shader shader) : _shader{std::make_unique<Shader>(shader)} {

}

Example::Example() {

}