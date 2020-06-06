#ifndef SDL_FRAMEWORK_ASSETMANAGER_H
#define SDL_FRAMEWORK_ASSETMANAGER_H

#include "renderer.h"
#include <string>
#include <map>

class AssetManager
{
private:
    static AssetManager *sInstance;

    std::map<std::string, SDL_Texture*> mText;
    std::map<std::string,TTF_Font*> mFonts;

public:
    static AssetManager* Instance();
    static void Release();

    // makes a text texture and returns text texture
    SDL_Texture* GetText(std::string text, std::string filename, int size);

private:
    AssetManager();
    ~AssetManager();

    // get font from the file and returns font
    TTF_Font* GetFont(std::string filename, int size);
};


#endif //SDL_FRAMEWORK_ASSETMANAGER_H
