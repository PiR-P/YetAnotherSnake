//
//  Cell.cpp
//  YetAnotherSnake
//
//  Created by Pierre Pasquet on 03/01/2018.
//  Copyright © 2018 Pierre Pasquet. All rights reserved.
//

#include "Cell.hpp"

Cell::Cell()
{
  /**
   Generate random coordinates for the pellet,
   depending on the number of cells in the grid so that the pellet doesn't spawn
   outside the world
  **/
  int rand_x(static_cast<int>(rand() % (CELLS_NB - 1) + 1));
  int rand_y(static_cast<int>(rand() % (CELLS_NB - 1 ) + 1));
  origin_ = std::make_pair(
   static_cast<float>(rand_x * CELL_SIZE),
   static_cast<float>(rand_y * CELL_SIZE)
  );
}

const bool Cell::isOutOfBound() const
{
  return (
    origin_.first + CELL_SIZE < WORLD_MIN ||
    origin_.first + CELL_SIZE > WORLD_MAX ||
    origin_.second + CELL_SIZE < WORLD_MIN ||
    origin_.second + CELL_SIZE > WORLD_MAX
  );
}

void Cell::draw() const
{
  glPushMatrix();
  glTranslatef(origin_.first, 0.0f, origin_.second);
  glScalef(CELL_SIZE, CELL_SIZE, CELL_SIZE);
  glutSolidCube(1.0);
  glPopMatrix();
}

bool Cell::operator==(const Cell &operand) const
{
  // Need to tolerate an espilon when comparing two floats
  return(
    (std::abs(origin_.first - operand.origin_.first) <= .001f) &&
    (std::abs(origin_.second - operand.origin_.second) <= .001f)
  );
}

Cell& Cell::operator=(const Cell &new_cell)
{
  origin_ = new_cell.origin();
  return *this;
}

std::pair<float, float> Cell::origin() const
{
  return origin_;
}
