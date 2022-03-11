#include <iostream>
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
        char* message = new char[length];//(char*)alloca(length * sizeof(char));
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