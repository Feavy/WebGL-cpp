#include "Person.h"
#include <iostream>

Person::Person(std::string name) : _name { name } {
}

void Person::sayHello() {
    std::cout << "Hello I am " << this->_name << "!" << std::endl;
}