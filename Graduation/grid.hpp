//
//  grid.hpp
//  Graduation
//
//  Created by Stefanos Mitropoulos on 31/03/2018.
//  Copyright © 2018 Stefanos Mitropoulos. All rights reserved.
//

#ifndef grid_hpp
#define grid_hpp

#include <stdio.h>
#include <vector>

std::vector<std::vector<char>>& initGrid(int gridX, int gridY);
void updateGrid(std::vector<std::vector<char>>& grid,int X,int Y,char V);
void updateGrid(std::vector<std::vector<char>>& grid,std::pair<int,int> position,char V);

void printGrid(std::vector<std::vector<char>>& grid);

#endif /* grid_hpp */

