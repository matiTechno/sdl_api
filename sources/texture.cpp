#include <texture.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

GLuint Texture::boundTexture{};

Texture::Texture(const char* filename)
{
    unsigned char* data = stbi_load(filename, &width, &height, nullptr, 4);
    if(data)
    {
        textureID.reset(new GLuint(), [](GLuint* textureID)
        {
            glDeleteTextures(1, textureID);
            delete textureID;
        });

        glGenTextures(1, textureID.get());
        glBindTexture(GL_TEXTURE_2D, *textureID);
        boundTexture = *textureID;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        stbi_image_free(data);
    }
    else
        std::cout << "TEXTURE_ERROR: could not load -> " << filename << std::endl;
}

void Texture::bind(GLuint unit)
{
    if(textureID != nullptr && *textureID != boundTexture)
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, *textureID);
        boundTexture = *textureID;
    }
}
