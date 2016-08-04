#include <shader.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

GLuint Shader::boundShader{};

Shader::Shader(const std::string& filename_noExt, bool isGS)
{
    // PHASE 1: shader compiling

    bool flag1{}, flag2{}, flag3{};

    GLuint vertexShader = compile(load(filename_noExt + ".vs"), GL_VERTEX_SHADER);
    GLuint fragmentShader = compile(load(filename_noExt + ".fs"), GL_FRAGMENT_SHADER);
    GLuint geometryShader{};
    if(isGS)
    {
        geometryShader =  compile(load(filename_noExt + ".gs"), GL_GEOMETRY_SHADER);
        flag3 = getShaderError(geometryShader, GL_COMPILE_STATUS, "SHADER_ERROR: compilation error -> " + filename_noExt + ".gs");
    }
    flag1 = getShaderError(vertexShader, GL_COMPILE_STATUS, "SHADER_ERROR: compilation error -> " + filename_noExt + ".vs");
    flag2 = getShaderError(fragmentShader, GL_COMPILE_STATUS, "SHADER_ERROR: compilation error -> " + filename_noExt + ".fs");

    if(flag1 || flag2 || flag3)
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        if(isGS)
            glDeleteShader(geometryShader);

        return;
    }
    // PHASE 2: program linking

    GLuint temp = glCreateProgram();

    glAttachShader(temp, vertexShader);
    glAttachShader(temp, fragmentShader);
    if(isGS)
        glAttachShader(temp, geometryShader);

    glLinkProgram(temp);

    if(getProgramError(temp, GL_LINK_STATUS, "SHADER_ERROR: could not link program"))
    {
        glDeleteProgram(temp);
    }
    else
    {
        glDetachShader(temp, vertexShader);
        glDetachShader(temp, fragmentShader);
        if(isGS)
            glDetachShader(temp, geometryShader);

        programID.reset(new GLuint(temp), [](GLuint* programID)
        {
            glDeleteProgram(*programID);
            delete programID;
        });
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if(isGS)
        glDeleteShader(geometryShader);
}

void Shader::bind()
{
    if(programID != nullptr && *programID != boundShader)
    {
        glUseProgram(*programID);
        boundShader = *programID;
    }
}

GLuint Shader::compile(const std::string& data, GLenum shaderType)
{
    GLuint shaderID = glCreateShader(shaderType);
    const GLchar* source[] = {data.c_str()};

    glShaderSource(shaderID, 1, source, nullptr);
    glCompileShader(shaderID);
    return shaderID;
}

std::string Shader::load(const std::string& filename)
{
    std::ifstream t(filename);
    if(t)
    {
        std::stringstream buffer;
        buffer << t.rdbuf();
        return buffer.str();
    }
    std::cout << "SHADER_ERROR: could not open -> " << filename << std::endl;
    return std::string();
}

bool Shader::getShaderError(GLuint shaderID, GLenum flag, const std::string& error_msg)
{
    GLint success = 0;
    glGetShaderiv(shaderID, flag, &success);

    if(success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);
        std::cout << error_msg << std::endl;

        for(std::vector<GLchar>::iterator i = infoLog.begin(); i != infoLog.end(); ++i)
            std::cout << *i;
        std::cout << std::endl;
        return true;
    }
    return false;
}

bool Shader::getProgramError(GLuint programID, GLenum flag, const std::string& error_msg)
{
    GLint success = 0;
    glGetProgramiv(programID, flag, &success);

    if(success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
        std::cout << error_msg << std::endl;

        for(std::vector<GLchar>::iterator i = infoLog.begin(); i != infoLog.end(); ++i)
            std::cout << *i;
        std::cout << std::endl;
        return true;
    }
    return false;
}
