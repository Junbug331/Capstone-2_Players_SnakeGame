#ifndef SNAKEGAME_FOOD_H
#define SNAKEGAME_FOOD_H

#include <random>
#include "snake.h"


class Food
{
public:
    Food() {}
    Food(int w_from, int w_to, int h_from, int h_to);
    int GetX() const;
    int GetY() const;
    void PlaceFood(Snake &snake);
    void Render(SDL_Renderer *renderer, SDL_Rect& block) const;

private:
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;
    SDL_Point point;
};


#endif //SNAKEGAME_FOOD_H
