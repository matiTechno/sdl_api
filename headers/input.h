#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <SDL2/SDL.h>

class Input
{
public:

    void clear_states();

    void keyDownEvent(const SDL_Event& event);

    void keyUpEvent(const SDL_Event& event);

    bool wasKeyPressed(SDL_Scancode key);

    bool wasKeyReleased(SDL_Scancode key);

    bool isKeyHeld(SDL_Scancode key);

private:

    std::map<SDL_Scancode, bool> keys1;
    std::map<SDL_Scancode, bool> keys2;
    std::map<SDL_Scancode, bool> keys3;
};

#endif // INPUT_H
