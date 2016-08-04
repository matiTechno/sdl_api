#include <input.h>

void Input::clear_states()
{
    keys1.clear();
    keys2.clear();
}

void Input::keyDownEvent(const SDL_Event& event)
{
    keys1[event.key.keysym.scancode] = true;
    keys3[event.key.keysym.scancode] = true;
}

void Input::keyUpEvent(const SDL_Event& event)
{
    keys2[event.key.keysym.scancode] = true;
    keys3.erase(event.key.keysym.scancode);
}

bool Input::wasKeyPressed(SDL_Scancode key)
{
    return keys1[key];
}

bool Input::wasKeyReleased(SDL_Scancode key)
{
    return keys2[key];
}

bool Input::isKeyHeld(SDL_Scancode key)
{
    return keys3[key];
}
