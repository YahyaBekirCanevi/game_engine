#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <malloc.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

/*! \struct ShaderSource
*   \brief Data read from .shader File
*/
struct ShaderSource {
    string vertexSource;
    string fragmentSource;
};

/*! \struct Vector2
*   \brief Position of vertex
*/
struct Vector2 {
    float x;
    float y;
};
//! Parse string from .shader File
static ShaderSource ParseShader(const string& filePath) {
    ifstream file(filePath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    stringstream ss[2];
    string line;
    ShaderType type = ShaderType::NONE;
    while (getline(file, line)) {
        if (line.find("#shader") != string::npos) {
            if (line.find("vertex") != string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != string::npos)
                type = ShaderType::FRAGMENT;
        }
        else {
            ss[(int)type] << line << "\n";
        }
    }
    return { ss[0].str(), ss[1].str() };
}
//! Compile vertex and fragment shaders
static unsigned int CompileShader(unsigned int type, const string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        cout << "Error on " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " : " << message << endl;
        glDeleteShader(id);

        return 0;
    }

    return id;
}
//! Creating and attaching shader to the program 
static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!window) { glfwTerminate(); return -1; }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Check if GLEW does work */
    if (glewInit() != GLEW_OK) cout << "Error" << endl;
    else cout << glGetString(GL_VERSION) << endl;

    /** Vertex Vector2 Position */
    Vector2 positions[3] 
    {{ 0.0f, 0.0f },
     { 0.0f, 0.5f },
     { 0.5f, 0.0f }};

    //* Generate and Bind Buffer */
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vector2), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), 0);

    /** Open .shader File */
    ShaderSource ss = ParseShader("Basic.shader");
    unsigned int shader = CreateShader(ss.vertexSource, ss.fragmentSource);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}