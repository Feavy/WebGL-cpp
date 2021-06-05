#include <string>

class Test {
private:
    std::string name;
public:
    Test(std::string name) : name(name) { }
    void call() {
        printf("Test %s\n", name.c_str());
    }
};