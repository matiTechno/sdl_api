#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <memory>

// shader filename must end with .vs/.gs/.fs

class Shader
{
public:

    Shader(const std::string& filename_noExt, bool isGS = false);

    void bind();

private:

    std::shared_ptr<GLuint> programID;

    static GLuint boundShader;

    GLuint compile(const std::string& data, GLenum shaderType);

    std::string load(const std::string& filename);

    bool getShaderError(GLuint shaderID, GLenum flag, const std::string& error_msg);

    bool getProgramError(GLuint programID, GLenum flag, const std::string& error_msg);
};

#endif // SHADER_H
