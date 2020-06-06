#include "AssetManager.h"
#include <iostream>

AssetManager* AssetManager::sInstance = nullptr;

AssetManager* AssetManager::Instance()
{
    if ( sInstance == nullptr)
        sInstance = new AssetManager();

    return sInstance;
}

void AssetManager::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
    for (auto text : mText)
    {
        if (text.second != NULL)
            SDL_DestroyTexture(text.second);
    }
    mText.clear();

    for (auto font : mFonts)
    {
        if (font.second != NULL)
            TTF_CloseFont(font.second);
    }

    mFonts.clear();
}

TTF_Font* AssetManager::GetFont(std::string filename, int size)
{
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("../assets/" + filename);
    std::string key = fullPath + (char)size;

    if (mFonts[key] == nullptr)
    {
        mFonts[key] = TTF_OpenFont(fullPath.c_str(), size);
        if (mFonts[key] == nullptr)
            std::cout << "Fonts Loading Error: Font-" << filename << " Error-" << TTF_GetError() << std::endl;
    }

    return mFonts[key];
}

SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size)
{
    TTF_Font* font = GetFont(filename, size);
    std::string key = text + filename + (char)size;

    if (mText[key] == nullptr)
        mText[key] = Renderer::Instance()->CreateTextTexture(font, text);

    return mText[key];
}


