#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

struct SDL_Window;
typedef void* SDL_GLContext;

class Sdl_window
{

public:

    Sdl_window(int width, int height);
    ~Sdl_window();

    bool isRunning;

private:

    SDL_Window* window;
    SDL_GLContext context;
};

#endif // SDL_WINDOW_H
