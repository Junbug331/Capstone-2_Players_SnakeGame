#include "game.h"

#include <iostream>
#include <thread>
#include <future>

Game* Game::sInstance = nullptr;

Game* Game::Instance()
{
    if (sInstance == nullptr)
        sInstance = new Game();

    return sInstance;
}

void Game::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

Game::Game()
{
    mRenderer = Renderer::Instance();
    mController = Controller::Instance();
    mFood1 = std::make_shared<Food>(1, static_cast<int>(Renderer::GRID_WIDTH)/2 - 1, 1, static_cast<int>(Renderer::GRID_HEIGHT) - 1 );
   mFood2 = std::make_shared<Food>(static_cast<int>(Renderer::GRID_WIDTH)/2 + 1, static_cast<int>(Renderer::GRID_WIDTH) - 1, 1, static_cast<int>(Renderer::GRID_HEIGHT) - 1);
   mSnake1 = std::make_shared<Snake>(Renderer::GRID_WIDTH/2, static_cast<int>(Renderer::GRID_HEIGHT), 0);
   mSnake2 = std::make_shared<Snake>(Renderer::GRID_WIDTH/2, static_cast<int>(Renderer::GRID_HEIGHT), Renderer::GRID_WIDTH/2);

   mController->SetEntity(&running,&playing ,mSnake1, mSnake2);
   controller_thread_ptr = new std::thread(&Controller::HandleInput, mController);
}

Game::~Game()
{
    Renderer::Release();
    Controller::Release();
    controller_thread_ptr->join();
}

void Game::Run()
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

    mRenderer->RenderStartScreen();

    while (running)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        if (!playing && !gameOver)
        {
            auto ftrEnter = std::async(&Controller::EnterKeyReturn, mController);
            ftrEnter.get();
        }

        if (playing && !gameOver)
        {
            frame_start = SDL_GetTicks();

            // Input, Update, Render - the main game loop
            Update();

            mRenderer->RenderGamePlay(mSnake1.get(), mSnake2.get(), mFood1.get(), mFood2.get());

            frame_end = SDL_GetTicks();

            // Keep track of how long each loop through the input/update/render cycle
            frame_count++;
            frame_duration = frame_end - frame_start;

            // After every second, update the window titlw
            if (frame_end - title_timestamp >= 1000)
            {
                mRenderer->UpdateWindowTitle(p1_score, p2_score, frame_count);
                frame_count = 0;
                title_timestamp = frame_end;
            }
            // If the time for this frame is too small (i.e. frame_duration is
            // smaller than the target ms_per_frame), delay the loop to
            // achieve the correct frame rate.
            if (frame_duration < Renderer::MsPerFrame)
            {
                SDL_Delay(Renderer::MsPerFrame - frame_duration);
            }
        }
        if (gameOver)
        {
            std::string winner = mSnake1->alive ? std::string("P1") : std::string("P2");
            mRenderer->RenderGameOverScreen(winner);
            auto ftrEnter = std::async(&Controller::EnterKeyReturn, mController);
            ftrEnter.get();
            Reset();
        }
    }
}

void Game::Reset()
{
    p1_score = 0;
    p2_score = 0;

    mSnake1->Reset();
    mSnake2->Reset();

    gameOver = false;
}

void Game::Update()
{
    if (!mSnake1->alive || !mSnake2->alive)
    {
        playing = false;
        gameOver = true;
        return;
    }
    mSnake1->Update();
    mSnake2->Update();

    if (mFood1->GetX() == static_cast<int>(mSnake1->head_x) && mFood1->GetY() == static_cast<int>(mSnake1->head_y))
    {
        p1_score++;
        mFood1->PlaceFood(*mSnake1);
        mSnake1->GrowBody();
        mSnake1->speed += 0.02;
    }

    if (mFood2->GetX() == static_cast<int>(mSnake2->head_x) && mFood2->GetY() == static_cast<int>(mSnake2->head_y))
    {
        p2_score++;
        mFood2->PlaceFood(*mSnake1);
        mSnake2->GrowBody();
        mSnake2->speed += 0.02;
    }
}


int Game::GetP1Score() const { return p1_score; }
int Game::GetP2Score() const { return p2_score; }
int Game::GetP1Size() const { return mSnake1->size; }
int Game::GetP2Size() const { return mSnake2->size; }