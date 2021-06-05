#pragma once

#include <string>

class Person {
public:
    Person(std::string name);
    void sayHello();
    void sayGoodbye();
private:
    std::string _name;
};