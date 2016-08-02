#include <game.h>
#include <SDL2/SDL.h>
#include <iostream>

Game::Game():
    window(640, 480)
{}

void Game::startLoop()
{
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

    window.display();
}
