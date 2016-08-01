#include <sdl_window.h>
#include <SDL2/SDL.h>

int main()
{
    Sdl_window window(640, 480);

    while(window.isRunning)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                window.isRunning = false;
        }
    }
    return 0;
}
