#include "shader.h"


std::string get_file_content(const char* filename) {
    std::cout << "Opening file: " << filename << std::endl;

    std::ifstream file(filename, std::ios::in);
    if (!file) {
        std::cerr << "ERROR: Cannot open file -> " << filename << std::endl;
        perror("Reason");
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::cout << buffer.str();
    return buffer.str();
}


Shader::Shader(const char* vertexFile,const char* fragmentFile){
    std::string vertexCode = get_file_content(vertexFile);
    std::string fragmentCode = get_file_content(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

    GLuint ID = glCreateProgram();

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    glLinkProgram(ID);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void Shader::Activate(){
    glUseProgram(ID);
}
void Shader::Delete(){
    glDeleteProgram(ID);
}