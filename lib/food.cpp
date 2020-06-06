#include "food.h"

Food::Food(int w_from, int w_to, int h_from, int h_to)
    : engine(dev()), random_w(w_from, w_to), random_h(h_from, h_to)
{
    point.x = random_w(engine);
    point.y = random_h(engine);
}

int Food::GetX() const { return point.x; }
int Food::GetY() const { return point.y; }

void Food::PlaceFood(Snake &snake)
{
    int x, y;
    while (true)
    {
        x = random_w(engine);
        y = random_h(engine);

        if (!snake.SnakeCell(x, y))
        {
            point.x = x;
            point.y = y;
            return;
        }
    }
}

void Food::Render(SDL_Renderer *renderer, SDL_Rect &block) const
{
    block.x = block.w * GetX();
    block.y = block.h * GetY();
    SDL_RenderFillRect(renderer, &block);
}
