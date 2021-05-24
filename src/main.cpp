#include <iostream>
#include <chrono>

#include "Person/Person.h"

using namespace std::chrono;

extern "C" {
    void helloJavascript();
 
    void hello() {
        std::cout << "Hello from C++!" << std::endl;
    }
}

int64_t get_time() {
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main() {
    Person person = Person {"Jean"};
    person.sayHello();
    std::cout << "Hello world!" << std::endl;
    std::cout << "Current time is " << get_time() << std::endl;
    helloJavascript();
    return 0;
}
