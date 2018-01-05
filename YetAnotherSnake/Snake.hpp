//
//  Snake.hpp
//  YetAnotherSnake
//
//  Created by Pierre Pasquet on 03/01/2018.
//  Copyright © 2018 Pierre Pasquet. All rights reserved.
//

#ifndef Snake_hpp
#define Snake_hpp

#include <deque>
#include "Snake_cell.hpp"

class Snake
{
public:
  Snake();
  
  Snake_cell& operator[](int i); // Access Snake's i-th cell
  Snake& operator++(); // Increment Snake's size
  Snake& operator=(const Snake& new_snake);
  friend std::ostream& operator<< (std::ostream &os, const Snake &snake);
  
  Direction getDirection() const;
  
  void setDirection(Direction new_direction);
  void move(); // 
  void draw() const; // Calls to OpenGL functions
  
  bool isOutOfBound() const; // Check if Snake is out of world's boundaries
  bool eatItself() const; // Check if Snake eats his trail
  
  int score() const;
  
private:
  std::deque<Snake_cell> cells_;
  Direction current_direction_;
};


#endif /* Snake_hpp */
