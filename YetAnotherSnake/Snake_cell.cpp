//
//  Snake_cell.cpp
//  YetAnotherSnake
//
//  Created by Pierre Pasquet on 03/01/2018.
//  Copyright © 2018 Pierre Pasquet. All rights reserved.
//

#include "Snake_cell.hpp"

Snake_cell::Snake_cell(const float origin_x, const float origin_z)
{
  // Create a pair of floats, representing respectively x and z coordinate
  Cell::origin_ = std::make_pair(origin_x, origin_z);
}

void Snake_cell::move(std::pair<float, float> new_origin)
{
  // Replace cell's origin with new one
  origin_ = new_origin;
}

