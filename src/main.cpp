#include <emscripten.h>
#include <emscripten/html5.h>
#include <webgl/webgl1.h>

#include <chrono>
#include <memory>

#include "Person/Person.h"
#include "Test.cpp"

using namespace std::chrono;

extern "C" {
void hello() { printf("Hello from C++\n"); }

void consoleLog(const char* str);
}
void consoleLog(const std::string& msg) { consoleLog(msg.c_str()); }

int64_t get_time() {
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
      .count();
}

GLuint LoadShader(GLenum type, const char* shaderSrc) {
  GLuint shader;
  GLint compiled;

  // Create the shader object
  shader = glCreateShader(type);

  if (shader == 0) return 0;

  // Load the shader source
  glShaderSource(shader, 1, &shaderSrc, NULL);

  // Compile the shader
  glCompileShader(shader);

  // Check the compile status
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

  if (!compiled) {
    GLint infoLen = 0;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

    if (infoLen > 1) {
      char* infoLog = (char*)malloc(sizeof(char) * infoLen);

      glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
      printf("Error compiling shader:\n%s\n", infoLog);

      free(infoLog);
    }

    glDeleteShader(shader);
    return 0;
  }

  return shader;
}

std::vector<int> testArray() {
  return {0, 1, 2, 3};
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
  std::unique_ptr<Person> person2{new Person{"Pierre"}};
  person2->sayHello();
  person.sayHello();
  std::string msg{"hello!"};
  printf("Hello world!\n");
  printf("Current time is %llu\n", get_time());
  consoleLog("console.log from C++");
  consoleLog(msg);

  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context =
      emscripten_webgl_create_context("canvas", nullptr);
  emscripten_webgl_make_context_current(context);
  emscripten_console_log("Context created");

  // OpenGL ES 2.0

  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  char vShaderStr[] =
      "attribute vec4 vPosition;    \n"
      "void main()                  \n"
      "{                            \n"
      "   gl_Position = vPosition;  \n"
      "}                            \n";

  char fShaderStr[] =
      "precision mediump float;\n"
      "void main()                                  \n"
      "{                                            \n"
      "  gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\n"
      "}                                            \n";

  GLuint vertexShader;
  GLuint fragmentShader;
  GLuint programObject;
  GLint linked;

  // Load the vertex/fragment shaders

  vertexShader = LoadShader(GL_VERTEX_SHADER, vShaderStr);
  fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fShaderStr);

  programObject = glCreateProgram();

  if (programObject == 0) return 0;

  glAttachShader(programObject, vertexShader);
  glAttachShader(programObject, fragmentShader);

    

  return 0;
}
