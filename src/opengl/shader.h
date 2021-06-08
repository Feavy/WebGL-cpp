#pragma once

#include <string>
#include <emscripten.h>
#include <emscripten/fetch.h>
#include <webgl/webgl1.h>
#include <map>

class Shader {
private:
    unsigned int ID;
    bool _loaded{false};
public:
    Shader(const char* vertexPath, const char* fragmentPath, std::map<int, std::string> attribLocations);

    bool loaded();

    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};