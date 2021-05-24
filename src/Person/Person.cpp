#include "Person.h"

Person::Person(std::string name) : _name { name } {
}

void Person::sayHello() {
    printf("Hello I am %s !\n", this->_name.c_str());
}