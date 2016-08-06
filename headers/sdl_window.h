#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

struct SDL_Window;
typedef void* SDL_GLContext;

class Sdl_window
{

public:

    Sdl_window(int width, int height);
    ~Sdl_window();

    void clear();
    void display();

    bool isRunning;

    int width, height;

    Sdl_window(const Sdl_window&) = delete;
    Sdl_window& operator=(const Sdl_window&) = delete;

private:

    SDL_Window* window;
    SDL_GLContext context;
};

#endif // SDL_WINDOW_H
