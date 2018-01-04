//
//  Cell.h
//  YetAnotherSnake
//
//  Created by Pierre Pasquet on 03/01/2018.
//  Copyright © 2018 Pierre Pasquet. All rights reserved.
//

#ifndef Cell_h
#define Cell_h

#include <iostream>
#include <stdio.h>
#include <utility> /** pair **/
#include <cstdlib> /** srand **/
#include <cmath> /** abs **/

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Utility.hpp"

class Cell
{
public:
  Cell();
  
  /** Check wether the cell is out of world's boundaries **/
  const bool isOutOfBound() const;
  /** Call to OpenGL drawing functions **/
  void draw() const;
  /** Overloading equal to operator **/
  bool operator==(const Cell& operand) const;
  Cell& operator=(const Cell& new_cell);
  std::pair<float, float> origin() const;
  
protected:
  std::pair<float, float> origin_;
};

#endif /* Cell_h */
