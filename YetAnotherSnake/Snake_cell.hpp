//
//  Snake_cell.hpp
//  YetAnotherSnake
//
//  Created by Pierre Pasquet on 03/01/2018.
//  Copyright © 2018 Pierre Pasquet. All rights reserved.
//

#ifndef Snake_cell_hpp
#define Snake_cell_hpp

#include "Cell.hpp"

class Snake_cell : public Cell
{
public:
  Snake_cell(const float origin_x, const float origin_y);
  
  /** Update cell's coordinate accordingly **/
  void move(std::pair<float, float> new_origin);
};

#endif /* Snake_cell_hpp */
