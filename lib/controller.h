#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <SDL2/SDL.h>
#include <memory>
#include <mutex>
class Controller {
private:
    static Controller* sInstance;

    std::shared_ptr<Snake> snake1;
    std::shared_ptr<Snake> snake2;
    bool *mGameState;
    bool *mPlaying;
    std::mutex _mutex;

public:
    static Controller* Instance();
    static void Release();

    // Set attributes for controller class
    void SetEntity(bool *gamestate, bool *playing ,std::shared_ptr<Snake> snake1, std::shared_ptr<Snake>snake2);

    // listener for Enter(Return) key
    int EnterKeyReturn();

    // listener for keyboard input for game play
    void HandleInput();


private:
    Controller();
    ~Controller();
    void ChangeDirection(Snake* snake, Snake::Direction input, Snake::Direction opposite);
};

#endif