#include "SDL.h"
#include "controller.h"
#include "snake.h"
#include <thread>
#include <mutex>


Controller* Controller::sInstance = nullptr;

Controller* Controller::Instance()
{
    if (sInstance == nullptr)
        sInstance = new Controller();

    return sInstance;
}

void Controller::ChangeDirection(Snake* snake, Snake::Direction input, Snake::Direction opposite)
{
    if (snake->direction != opposite || snake->size == 1)
    {
        snake->direction = input;
    }
    return;
}

void Controller::SetEntity(bool *gamestate, bool *playing ,std::shared_ptr<Snake> snake1, std::shared_ptr<Snake> snake2)
{
    this->snake1 = snake1;
    this->snake2 = snake2;
    mGameState = gamestate;
    mPlaying = playing;
}

void Controller::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

Controller::Controller() {}

Controller::~Controller()
{

}

int Controller::EnterKeyReturn()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {

        if (e.type == SDL_QUIT) {
            std::lock_guard<std::mutex> lock(_mutex);
            *mGameState = false;
            return 1;
        }

        else if (e.key.keysym.sym == SDLK_RETURN)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            *mPlaying = true;
            return 1;
        }
    }

    return 1;
}

void Controller::HandleInput()
{
    while(*mGameState)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                *mGameState = false;
            }
            else if (e.type == SDL_KEYDOWN) {
                std::lock_guard<std::mutex> lock(_mutex);
                switch (e.key.keysym.sym) {
                    case SDLK_w:
                        ChangeDirection(snake1.get(), Snake::Direction::kUp,Snake::Direction::kDown);
                        break;

                    case SDLK_s:
                        ChangeDirection(snake1.get(), Snake::Direction::kDown,Snake::Direction::kUp);
                        break;

                    case SDLK_a:
                        ChangeDirection(snake1.get(), Snake::Direction::kLeft,Snake::Direction::kRight);
                        break;
                    case SDLK_d:
                        ChangeDirection(snake1.get(), Snake::Direction::kRight,Snake::Direction::kLeft);
                        break;
                    case SDLK_UP:
                        ChangeDirection(snake2.get(), Snake::Direction::kUp,Snake::Direction::kDown);
                        break;

                    case SDLK_DOWN:
                        ChangeDirection(snake2.get(), Snake::Direction::kDown,Snake::Direction::kUp);
                        break;

                    case SDLK_LEFT:
                        ChangeDirection(snake2.get(), Snake::Direction::kLeft,Snake::Direction::kRight);
                        break;

                    case SDLK_RIGHT:
                        ChangeDirection(snake2.get(), Snake::Direction::kRight,Snake::Direction::kLeft);
                        break;
                    case SDLK_l:
                        snake1->alive = false;
                        break;
                }
            }
        }
    }
}