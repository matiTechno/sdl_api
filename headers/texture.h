#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>
#include <memory>

class Texture
{
public:

    Texture(const char* filename);

    void bind(GLuint unit = 0);

    int width, height;

private:

    std::shared_ptr<GLuint> textureID;

    static GLuint boundTexture;
};

#endif // TEXTURE_H
