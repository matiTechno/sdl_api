#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <GL/glew.h>
#include <memory>

class Shader;
class Sprite;

class Sprite_renderer
{
public:

    Sprite_renderer();

    void draw(Shader& shader, Sprite& sprite);

private:

    std::shared_ptr<GLuint> VAO, VBO;
};

#endif // SPRITE_RENDERER_H
