#include "Person.h"

Person::Person(std::string name) : _name { name } {
}

void Person::sayGoodbye() {
    printf("Goodbye\n");
}

void Person::sayHello() {
    auto goodbye = &Person::sayGoodbye;
    printf("Hello I am %s !\n", _name.c_str());
    (this->*goodbye)();
}
