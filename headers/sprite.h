#ifndef SPRITE_H
#define SPRITE_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class Texture;

class Sprite
{
public:

    // (0,0) (1,0)
    // (0,1) (1,1)
    // sprite coordinates

    Sprite(const glm::vec2& position, const glm::vec2& size, Texture& texture, const glm::vec4& texCoords,
           glm::vec2 rotation_point = glm::vec2(0.5f, 0.5f), GLfloat rotation = 0.f, const glm::vec4& color = glm::vec4(1.f, 1.f, 1.f, 1.f)):

        position(position),
        size(size),
        texture(texture),
        texCoords(texCoords),
        rotation_point(rotation_point),
        rotation(rotation),
        color(color){}

    glm::vec2 position;

    glm::vec2 size;

    Texture& texture;

    glm::vec4 texCoords;

    glm::vec2 rotation_point;

    GLfloat rotation;

    glm::vec4 color;
};

#endif // SPRITE_H
