//
// Created by jun on 20. 5. 13..
//

#include "Text.h"

Text::Text(std::string text, std::string fontPath, int size)
{
    mTex = AssetManager::Instance()->GetText(text, fontPath, size);

    SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

    mRenderRect.w = mWidth;
    mRenderRect.h = mHeight;
}

Text::~Text()
{

}

void Text::Pos(float x, float y)
{
    pos.x = static_cast<int>(x);
    pos.y = static_cast<int>(y);
}

void Text::Render(SDL_Renderer *renderer)
{
    mRenderRect.x = pos.x - mWidth / 2;
    mRenderRect.y = pos.y - mHeight / 2;

    SDL_RenderCopy(renderer, mTex, NULL, &mRenderRect);
}


