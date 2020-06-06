#ifndef SNAKEGAME_TEXT_H
#define SNAKEGAME_TEXT_H

#include "AssetManager.h"

class Text
{
private:
    SDL_Point pos;
    SDL_Texture *mTex;

    int mWidth;
    int mHeight;

    SDL_Rect mRenderRect;

public:
    Text() {}
    Text(std::string text, std::string fontPath, int size);
    ~Text();
    void Pos(float x, float y);
    void Render(SDL_Renderer *renderer);
};


#endif //SNAKEGAME_TEXTURE_H
