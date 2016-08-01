#include "sdl_window.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <GL/glew.h>

Sdl_window::Sdl_window(int width, int height):

    isRunning(true)
{
    /*The Event Handling subsystem is initialized implicitly by the Video subsystem.*/
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    this->window = SDL_CreateWindow("opengl_api", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if(!this->window)
    {
        std::cout << "could not create window: " << SDL_GetError() << std::endl;
        isRunning = false;
    }

    /*Returns the OpenGL context associated with window or NULL on error; call SDL_GetError() for more details.*/
    this->context = SDL_GL_CreateContext(this->window);
    if(!this->context)
    {
        std::cout << "opengl context creation failure: " << SDL_GetError() << std::endl;
        isRunning = false;
    }

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong.*/
        std::cout << "glew not working" << std::endl;
        isRunning = false;
    }
}

Sdl_window::~Sdl_window()
{
    SDL_GL_DeleteContext(this->context);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
