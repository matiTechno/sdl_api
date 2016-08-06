#include <sprite_renderer.h>
#include <glm/gtx/transform.hpp>
#include <shader.h>
#include <sprite.h>
#include <texture.h>

Sprite_renderer::Sprite_renderer()
{
    GLfloat vertices[] = {0.f, 0.f, 0.f, 0.f,
                          1.f, 0.f, 1.f, 0.f,
                          1.f, 1.f, 1.f, 1.f,

                          1.f, 1.f, 1.f, 1.f,
                          0.f, 1.f, 0.f, 1.f,
                          0.f, 0.f, 0.f, 0.f};

    VAO.reset(new GLuint, [](GLuint* VAO)
    {
        glDeleteVertexArrays(1, VAO);
        delete VAO;
    });

    VBO.reset(new GLuint, [](GLuint* VBO)
    {
        glDeleteBuffers(1, VBO);
        delete VBO;
    });

    glGenVertexArrays(1, VAO.get());
    glBindVertexArray(*VAO);

    glGenBuffers(1, VBO.get());
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
}

void Sprite_renderer::draw(Shader& shader, Sprite& sprite)
{
    shader.bind();
    sprite.texture.bind();

    glm::mat4 model;

    model = glm::translate(model, glm::vec3(sprite.position, 0.f));

    model = glm::translate(model, glm::vec3(sprite.rotation_point * sprite.size, 0.f));
    model = glm::rotate(model, sprite.rotation, glm::vec3(0.f, 0.f, -1.f));
    model = glm::translate(model, glm::vec3(-sprite.rotation_point * sprite.size, 0.f));

    model = glm::scale(model, glm::vec3(sprite.size, 1.f));

    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "model"), 1, GL_FALSE, &model[0][0]);
    glUniform4f(glGetUniformLocation(shader.getID(), "sprite_color"), sprite.color.x, sprite.color.y, sprite.color.z, sprite.color.w);

    glm::vec2 texSides(GLfloat(sprite.texCoords.z - sprite.texCoords.x)/sprite.texture.width,
                       GLfloat(sprite.texCoords.w - sprite.texCoords.y)/sprite.texture.height);

    glm::vec2 texShift(GLfloat(sprite.texCoords.x)/sprite.texture.width,
                       GLfloat(sprite.texCoords.y)/sprite.texture.height);

    glUniform2f(glGetUniformLocation(shader.getID(), "texSides"), texSides.x, texSides.y);
    glUniform2f(glGetUniformLocation(shader.getID(), "texShift"), texShift.x, texShift.y);

    GLint boundVAO;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &boundVAO);
    if(*VAO != static_cast<GLuint>(boundVAO))
        glBindVertexArray(*VAO);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
