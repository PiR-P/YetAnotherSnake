//
//  Utility.hpp
//  YetAnotherSnake
//
//  Created by Pierre Pasquet on 03/01/2018.
//  Copyright © 2018 Pierre Pasquet. All rights reserved.
//

#ifndef Utility_h
#define Utility_h

const int CELLS_NB { 40 }; /** Number of cells on the board **/
const float WORLD_MIN { 0.0f };
const float WORLD_MAX { 1.0f };
const float CELL_SIZE { WORLD_MAX / CELLS_NB };
const int TIMER_DELAY { 80 };

enum Direction { north = 0, east = 1, south = 2, west = 3 };

#endif /* Utility_h */
