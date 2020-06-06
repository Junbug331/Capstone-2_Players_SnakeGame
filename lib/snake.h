//
// Created by jun on 20. 5. 8..
//

#ifndef SDL_GRAPHIC_SNAKE_H
#define SDL_GRAPHIC_SNAKE_H

#include <SDL2/SDL.h>
#include <vector>

class Snake {
public:
    enum class Direction {kUp, kDown, kLeft, kRight};
    Snake() {}
    Snake(int grid_width, int grid_height, int grid_scalar);


    void Update();
    void Reset();
    void GrowBody();
    // check if a cell is occupied by a snake entity
    bool SnakeCell(int& x, int& y) const;
    void Render(SDL_Renderer *renderer, SDL_Rect &block) const;

    Direction direction = Direction::kUp;

    float speed{0.1f};
    int size{1};
    bool alive{true};
    float head_x;
    float head_y;

    std::vector<SDL_Point> body;

private:
    void UpdateHead();
    void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

    bool growing{false};
    int grid_width;
    int grid_height;
    int grid_scalar;
};

#endif //SDL_GRAPHIC_SNAKE_H
