#ifndef GAME_H
#define GAME_H

// Remember to clean opengl stuff before deleting context!

#include <sdl_window.h>
#include <input.h>
#include <vector>
#include <texture.h>
#include <shader.h>
#include <sprite_renderer.h>
#include <sprite.h>

class Game{

public:

    Game();

    void startLoop();

private:

    void processInput();
    void update();
    void render();
    void init();

    // memebers
    Sdl_window window;
    Input input;

    std::vector<Texture> textures;
    std::vector<Shader> shaders;
    std::vector<Sprite_renderer> renderers;
    std::vector<Sprite> sprites;
};

#endif // GAME_H
