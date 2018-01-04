//
//  Snake_cell.cpp
//  YetAnotherSnake
//
//  Created by Pierre Pasquet on 03/01/2018.
//  Copyright © 2018 Pierre Pasquet. All rights reserved.
//

#include "Snake_cell.hpp"

Snake_cell::Snake_cell(const float origin_x, const float origin_y)
{
  Cell::origin_ = std::make_pair(origin_x, origin_y);
}

void Snake_cell::move(std::pair<float, float> new_origin)
{
  origin_ = new_origin;
}

