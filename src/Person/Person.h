#pragma once

#include <string>

class Person {
public:
    Person(std::string name);
    void sayHello();
private:
    std::string _name;
};