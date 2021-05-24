#include <chrono>
#include <memory>
#include "Person/Person.h"

using namespace std::chrono;

extern "C" {
    void hello() {
        printf("Hello from C++\n");
    }

    void consoleLog(const char* str);

}
void consoleLog(const std::string &msg) {
    consoleLog(msg.c_str());
}

int64_t get_time() {
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main() {
    Person person = Person {"Jean"};
    std::unique_ptr<Person> person2{new Person{"Pierre"}};
    person2->sayHello();
    person.sayHello();
    std::string msg{"hello!"};
    printf("Hello world!\n");
    printf("Current time is %llu\n", get_time());
    consoleLog("console.log from C++");
    consoleLog(msg);
    return 0;
}
