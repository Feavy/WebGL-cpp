#include <chrono>
#include <memory>

#include "Person/Person.h"

using namespace std::chrono;

extern "C" {
    void helloJavascript();
 
    void hello() {
        printf("Hello from C++\n");
    }
}

int64_t get_time() {
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main() {
    Person person = Person {"Jean"};
    std::unique_ptr<Person> person2{new Person{"Pierre"}};
    person2->sayHello();
    person.sayHello();
    printf("Hello world!\n");
    printf("Current time is %d\n", get_time());
    helloJavascript();
    return 0;
}
