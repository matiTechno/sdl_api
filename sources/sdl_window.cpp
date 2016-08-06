#include <sdl_window.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <GL/glew.h>

Sdl_window::Sdl_window(int width, int height):

    isRunning(false),
    width(width),
    height(height)
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

    window = SDL_CreateWindow("opengl_api", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if(!window)
    {
        std::cout << "INIT_ERROR: could not create SDL_Window: " << SDL_GetError() << std::endl;
        return;
    }

    /*Returns the OpenGL context associated with window or NULL on error; call SDL_GetError() for more details.*/
    context = SDL_GL_CreateContext(window);
    if(!context)
    {
        std::cout << "INIT_ERROR: opengl context creation failure: " << SDL_GetError() << std::endl;
        return;
    }

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong.*/
        std::cout << "INIT_ERROR: GLEW not working" << std::endl;
        return;
    }

    SDL_GL_SetSwapInterval(1); // Vsync
    // some early opengl configuration
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    isRunning = true;
}

Sdl_window::~Sdl_window()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Sdl_window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Sdl_window::display()
{
    SDL_GL_SwapWindow(window);
}
