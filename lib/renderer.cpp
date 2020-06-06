#include "renderer.h"
#include "Text.h"

Renderer* Renderer::sInstance = nullptr;
bool Renderer::sInitialized = false;

Renderer* Renderer::Instance()
{
    if (sInstance == nullptr)
        sInstance = new Renderer();
    return sInstance;
}

void Renderer::Release()
{
    AssetManager::Release();
    delete sInstance;
    sInstance = nullptr;
    sInitialized = false;
}

Renderer::Renderer()
{
    sInitialized = Init();
}

bool Renderer::Init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create Window
    sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (sdl_window == nullptr)
    {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }
    //Create Renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);

    if (nullptr == sdl_renderer)
    {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xFF);

    if (TTF_Init() == -1)
    {
        std::cerr << "TTF Initialization Error.\n";
        std::cerr << "SDL_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

Renderer::~Renderer()
{
    std::cout << "Renderer destructor called!" << std::endl;
    SDL_DestroyWindow(sdl_window);
    SDL_DestroyRenderer(sdl_renderer);
    SDL_Quit();
}

void Renderer::RenderGamePlay(const Snake* snake1, const Snake* snake2, const Food* food1, const Food* food2)
{
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Draw Screen Divider
    SDL_Rect block;
    block.w = SCREEN_WIDTH / GRID_WIDTH;
    block.h = SCREEN_HEIGHT;
    block.x =  GRID_WIDTH/2  * block.w;
    block.y = 0;
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(sdl_renderer, &block);

    // Render Foods
    block.h = SCREEN_HEIGHT / GRID_HEIGHT;

    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    food1->Render(sdl_renderer, block);
    food2->Render(sdl_renderer, block);

    // Render snakes' body and head
    snake1->Render(sdl_renderer, block);
    snake2->Render(sdl_renderer, block);

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderStartScreen()
{
    SDL_RenderClear(sdl_renderer);

    Text text("Press Enter to Play", "ARCADE.TTF", 22);
    text.Pos(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.3f);
    text.Render(sdl_renderer);

    SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderGameOverScreen(std::string winner)
{
    Text text1("GAME OVER", "ARCADE.TTF", 22);
    text1.Pos(SCREEN_WIDTH/2, SCREEN_HEIGHT/6);

    Text text2(winner.append(" WON!"), "ARCADE.TTF", 22);
    text2.Pos(SCREEN_WIDTH/2, SCREEN_HEIGHT/4);

    Text text3("ENTER TO REPLAY", "ARCADE.TTF", 22);
    text3.Pos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(sdl_renderer);

    text1.Render(sdl_renderer);
    text2.Render(sdl_renderer);
    text3.Render(sdl_renderer);

    SDL_RenderPresent(sdl_renderer);
}


SDL_Texture * Renderer::CreateTextTexture(TTF_Font *font, std::string text)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), {245, 245, 245});
    if (surface == NULL)
    {
        std::cerr << "Text Render Error: " << TTF_GetError() << "\n";
        return NULL;
    }

    SDL_Texture * tex = SDL_CreateTextureFromSurface(sdl_renderer, surface);
    if (tex == NULL)
    {
        std::cerr << "Text Creation Error: " << SDL_GetError();
        return NULL;
    }

    SDL_FreeSurface(surface);

    return tex;
}

void Renderer::UpdateWindowTitle(int& p1_score, int& p2_score, int& fps)
{
    std::string title{"Player1  score: " + std::to_string(p1_score) + "  |  Player2  score: " + std::to_string(p2_score) + "   FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
}