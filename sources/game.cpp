#include <game.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <glm/gtx/transform.hpp>

Game::Game():
    window(640, 480)
{}

void Game::startLoop()
{
    if(!window.isRunning)
        return;

    init();

    // Since SDL_GetTicks() returns an unsigned int value I decided to make 'dt' and 'accumulator' the same type.
    const unsigned int dt = 17; // ~(1000 ms / 60)

    unsigned int currentTime = SDL_GetTicks();
    unsigned int accumulator = 0;

    while(window.isRunning)
    {
        processInput();

        unsigned int newTime = SDL_GetTicks();
        unsigned int frameTime = newTime - currentTime;
        currentTime = newTime;

        std::cout << frameTime << std::endl;

        accumulator += frameTime;

        while(accumulator >= dt)
        {
            update();
            accumulator -= dt;
        }
        // to do: interpolation
        render();
    }
}

void Game::processInput()
{
    input.clear_states();
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            window.isRunning = false;

        else if(event.type == SDL_KEYDOWN && !event.key.repeat)
            input.keyDownEvent(event);

        else if(event.type == SDL_KEYUP && !event.key.repeat)
            input.keyUpEvent(event);
    }
    if(input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
        window.isRunning = false;
}

void Game::update()
{

}

void Game::render()
{
    window.clear();
    renderers[0].draw(shaders[0], sprites[0]);
    window.display();
}

void Game::init()
{
    textures.push_back(Texture("res/texture.png"));
    shaders.push_back(Shader("res/shader"));
    renderers.push_back(Sprite_renderer());
    sprites.push_back(Sprite(glm::vec2(0, 0), glm::vec2(200, 200), textures[0],
                      glm::vec4(0, 0, textures[0].width, textures[0].height)));

    shaders[0].bind();
    glm::mat4 projection = glm::ortho(0.f, GLfloat(window.width), GLfloat(window.height), 0.f);
    glUniformMatrix4fv(glGetUniformLocation(shaders[0].getID(), "projection"), 1, GL_FALSE, &projection[0][0]);
}
