//
// Created by jun on 20. 5. 8..
//

#ifndef SDL_GRAPHIC_RENDERER_H
#define SDL_GRAPHIC_RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "snake.h"
#include "food.h"

class Text;

class Renderer
{
public:
    static const std::size_t SCREEN_WIDTH = 640 * 2;
    static const std::size_t SCREEN_HEIGHT = 640;
    static const std::size_t GRID_WIDTH = 32 * 2;
    static const std::size_t GRID_HEIGHT = 32;
    static const std::size_t FPS = 60;
    static const std::size_t MsPerFrame = 1000 / FPS;

private:
    static Renderer* sInstance;
    static bool sInitialized;


    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

public:
    static Renderer* Instance();
    static void Release();

    // renders initial game screen
    void RenderStartScreen();

    // renders game play
    void RenderGameOverScreen(std::string winner);

    // renders post game screen
    void RenderGamePlay(const Snake* snake1, const Snake* snake2, const Food* food1, const Food* food2);

    // returns a texture pointer for the text with font applied
    SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text);

    void UpdateWindowTitle(int& p1_score, int& p2_score, int& fps);

private:
    Renderer();
    ~Renderer();
    bool Init();
};


#endif //SDL_GRAPHIC_RENDERER_H
