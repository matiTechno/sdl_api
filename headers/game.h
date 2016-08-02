#ifndef GAME_H
#define GAME_H

// Remember to clean opengl stuff before deleting context!

#include <sdl_window.h>
#include <input.h>

class Game{

public:

    Game();

    void startLoop();

private:

    void processInput();
    void update();
    void render();

    // memebers
    Sdl_window window;
    Input input;
};

#endif // GAME_H
