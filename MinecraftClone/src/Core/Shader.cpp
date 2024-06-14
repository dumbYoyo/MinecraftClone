#include "Shader.h"

void Shader::Init(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexShaderCode = ReadShaderFile(vertexPath);
    std::string fragmentShaderCode = ReadShaderFile(fragmentPath);

    const char* vertexCode = vertexShaderCode.c_str();
    const char* fragmentCode = fragmentShaderCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    Id = glCreateProgram();
    glAttachShader(Id, vertex);
    glAttachShader(Id, fragment);
    glLinkProgram(Id);
    glGetProgramiv(Id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(Id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Bind()
{
    glUseProgram(Id);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::LoadMat4f(const char* uniformName, const glm::mat4& data)
{
    unsigned int loc = glGetUniformLocation(Id, uniformName);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(data));
}

void Shader::LoadInt(const char* uniformName, int data)
{
    unsigned int loc = glGetUniformLocation(Id, uniformName);
    glUniform1i(loc, data);
}

void Shader::LoadVec3(const char* uniformName, const glm::vec3& data)
{
    unsigned int loc = glGetUniformLocation(Id, uniformName);
    glUniform3f(loc, data.x, data.y, data.z);
}

void Shader::CleanUp()
{
    glDeleteProgram(Id);
}

std::string Shader::ReadShaderFile(const char* filePath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string code;
    std::ifstream shaderFile;
    // ensure ifstream objects can throw exceptions:
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        shaderFile.open(filePath);
        std::stringstream shaderStream;
        // read file's buffer contents into streams
        shaderStream << shaderFile.rdbuf();
        // close file handlers
        shaderFile.close();
        // convert stream into string
        code = shaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    return code;
}
