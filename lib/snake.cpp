//
// Created by jun on 20. 5. 8..
//

#include "snake.h"

// Constructor
Snake::Snake(int grid_width, int grid_height, int grid_scalar)
        : grid_width(grid_width), grid_height(grid_height), grid_scalar(grid_scalar)
{
    head_x = static_cast<float>(grid_width / 2 + grid_scalar);
    head_y = grid_height / 2;
    if (grid_scalar > 0)
        this->grid_scalar++;
}

void Snake::Reset()
{
    speed = 0.1f;
    size = 1;
    alive = true;
    head_x = static_cast<float>(grid_width / 2 + grid_scalar);
    head_y = grid_height / 2;
    body.clear();
}

void Snake::Update()
{
    SDL_Point prev_cell{static_cast<int>(head_x), static_cast<int>(head_y)};
    UpdateHead();
    // Capture the head's cell after updating.
    SDL_Point current_cell{static_cast<int>(head_x),static_cast<int>(head_y)};

    // Update all of the body vector items if the snake head has moved to a new
    // cell.
    if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
        UpdateBody(current_cell, prev_cell);
}


void Snake::UpdateHead()
{
    switch (direction)
    {
        case Direction::kUp:
            head_y -= speed;
            break;

        case Direction::kDown:
            head_y += speed;
            break;

        case Direction::kLeft:
            head_x -= speed;
            break;

        case Direction::kRight:
            head_x += speed;
            break;
    }

    // Wrap the Snake around to the beginning if going off of the screen
    head_x -= grid_scalar;
    head_x = fmod(head_x + grid_width, grid_width);
    head_x += grid_scalar;
    head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell)
{
    // Add previous head location to vector
    body.push_back(prev_head_cell);

    if (!growing)
        // Remove the tail from the vector.
        body.erase(body.begin());
    else
    {
        growing = false;
        size++;
    }

    // Check if the snake has died
    for (auto const &item : body)
    {
        if (current_head_cell.x == item.x && current_head_cell.y == item.y)
            alive = false;
    }
}


void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int& x, int& y) const
{
    if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y))
        return true;

    for (auto const &item : body)
    {
        if ( x == item.x && y == item.y)
            return true;
    }

    return false;
}

void Snake::Render(SDL_Renderer* renderer, SDL_Rect &block) const
{
    // Draw Body
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const &point : body)
    {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(renderer, &block);
    }

    // Draw head
    block.x = static_cast<int>(head_x) * block.w;
    block.y = static_cast<int>(head_y) * block.h;

    if (alive)
        SDL_SetRenderDrawColor(renderer, 0x00, 0x7A, 0xCC, 0xFF);
    else
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &block);
}