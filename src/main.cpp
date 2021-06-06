#include <emscripten.h>
#include <emscripten/html5.h>

#include <chrono>
#include <memory>

#include "Person/Person.h"
#include "Test.cpp"

#include "opengl.h"

using namespace std::chrono;

extern "C" {
void hello() { printf("Hello from C++\n"); }

void consoleLog(const char *str);
}

void consoleLog(const std::string &msg) { consoleLog(msg.c_str()); }

int64_t get_time() {
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
        .count();
}

int main() {
    Test test{"Test1"};
    test.call();
    emscripten_run_script("document.body.innerHTML += '<p>Bonjour !</p>';");
    EM_ASM(const p = document.createElement('p'); p.innerText = "ça marche !";
           document.body.append(p););
    double perf = emscripten_performance_now();
    std::string val = "performance " + std::to_string(perf);
    emscripten_console_log(val.c_str());
    Person person = Person{"Jean"};
    auto person2 = std::make_unique<Person>("Pierre");
    person2->sayHello();
    person.sayHello();
    std::string msg{"hello!"};
    printf("Hello world!\n");
    printf("Current time is %llu\n", get_time());
    consoleLog("console.log from C++");
    consoleLog(msg);

    opengl_init();

    return 0;
}
