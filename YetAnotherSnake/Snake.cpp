//
//  Snake.cpp
//  YetAnotherSnake
//
//  Created by Pierre Pasquet on 03/01/2018.
//  Copyright © 2018 Pierre Pasquet. All rights reserved.
//

#include "Snake.hpp"

std::ostream& operator<<(std::ostream& os, const Snake& snake)
{
  for(auto it = snake.cells_.begin(); it != snake.cells_.end(); ++it)
  {
    os << (*it).origin().first << "\t" << (*it).origin().second << std::endl;
  }
  return os;
}

Snake::Snake() : current_direction_(Direction::north)
{
  const float first_cell { WORLD_MAX / 2.0f };
  
  cells_.emplace_back(first_cell + 2 * CELL_SIZE, first_cell);
  cells_.emplace_back(first_cell + CELL_SIZE, first_cell);
  cells_.emplace_back(first_cell, first_cell);
}

Snake_cell& Snake::operator[](int i)
{
  return cells_[i];
}

Snake& Snake::operator++()
{
  cells_.emplace_back(
    cells_.back().origin().first,
    cells_.back().origin().second
  );
  return *this;
}

Snake& Snake::operator=(const Snake& new_snake)
{
  cells_ = new_snake.cells_;
  current_direction_ = new_snake.current_direction_;
  return *this;
}

void Snake::setDirection(Direction new_direction)
{
  if(current_direction_ != new_direction)
  {
    if(std::abs(current_direction_ - new_direction) != 2)
      current_direction_ = new_direction;
  }
}

void Snake::move()
{
  // ith cell takes i-1th cell's position, except the front cell
  for(auto it = cells_.rbegin(); it != cells_.crend() - 1; ++it)
  {
    auto iterator = it;
    Snake_cell& cell = *iterator;
    Snake_cell& adjacent_cell = *(++iterator);
    cell = adjacent_cell;
  }
  
  Snake_cell &front_cell = cells_[0];
  switch(current_direction_)
  {
    case Direction::north:
      front_cell = Snake_cell(front_cell.origin().first + CELL_SIZE, front_cell.origin().second);
      break;
    case Direction::east:
      front_cell = Snake_cell(front_cell.origin().first, front_cell.origin().second + CELL_SIZE);
      break;
    case Direction::south:
      front_cell = Snake_cell(front_cell.origin().first - CELL_SIZE, front_cell.origin().second);
      break;
    case Direction::west:
      front_cell = Snake_cell(front_cell.origin().first, front_cell.origin().second - CELL_SIZE);
      break;
    default:
      break;
  }
}

void Snake::draw() const
{
  for(auto it = cells_.begin(); it != cells_.cend(); ++it)
  {
    const Snake_cell& cell = *it;
    cell.draw();
  }
}

bool Snake::isOutOfBound() const
{
  for(auto it = cells_.begin(); it != cells_.cend(); ++it)
  {
    const Snake_cell& cell = *it;
    if(cell.isOutOfBound())
      return true;
  }
  return false;
}

bool Snake::eatItself() const
{
  const Snake_cell& front_cell = cells_[0];
  for(auto it = cells_.begin() + 1; it != cells_.cend(); ++it)
  {
    const Snake_cell& cell = *it;
    if(cell == front_cell)
      return true;
  }
  return false;
}

int Snake::score() const
{
  // Initial Snake's size is 3
  return (cells_.size() - 3);
}


