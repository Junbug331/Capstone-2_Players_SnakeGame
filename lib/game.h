#ifndef MULTIPLAY_SNAKEGAME_GAME_H
#define MULTIPLAY_SNAKEGAME_GAME_H

#include <random>
#include <SDL2/SDL.h>
#include "controller.h"
#include "snake.h"
#include "food.h"
#include "renderer.h"
#include <thread>
#include <memory>
class Game
{
private:
    static Game* sInstance;
    Renderer* mRenderer;
    Controller* mController;

    std::shared_ptr<Snake> mSnake1;
    std::shared_ptr<Snake> mSnake2;
    std::shared_ptr<Food> mFood1;
    std::shared_ptr<Food> mFood2;

    std::thread *controller_thread_ptr;

    bool running = true;
    bool playing = false;
    bool gameOver = false;
    int p1_score{0};
    int p2_score{0};



public:
    // Returns Game instance
    static Game* Instance();

    // Clean the memory
    static void Release();

    // Starts the game
    void Run();
    // Reset the game data
    void Reset();

    int GetP1Score() const;
    int GetP2Score() const;
    int GetP1Size() const;
    int GetP2Size() const;
private:
    Game();
    ~Game();
    void Update();
};


#endif //MULTIPLAY_SNAKEGAME_GAME_H
