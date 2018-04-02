	//
	//  grid.cpp
	//  Graduation
	//
	//  Created by Stefanos Mitropoulos on 31/03/2018.
	//  Copyright © 2018 Stefanos Mitropoulos. All rights reserved.
	//

#include "grid.hpp"
#include <iostream>


std::vector<std::vector<char>>& initGrid(int gridX, int gridY){
		//declare the vector on the heap. The default constructor would assign stack memory and when out of scope of the fuctnion, the object would be deleted.
	static std::vector< std::vector<char> > grid (gridY, std::vector<char>(gridX,'.'));
	return grid;

}

//"draw" the grid position with the given sprite
void updateGrid(std::vector<std::vector<char>>& grid,int X,int Y,char V){
	grid[X][Y]=V;
}

	//"draw" the grid position with the given sprite
void updateGrid(std::vector<std::vector<char>>& grid, std::pair<int,int> position, char V){
	grid[position.first][position.second]=V;
}


//Print the whole grid
void printGrid(std::vector<std::vector<char>>& grid){
	for (int rows=0;rows<grid.size();rows++){
		for (int cols=0;cols<grid[rows].size();cols++){
			std::cout<< grid[rows][cols]<<std::flush;
		}
		std::cout<<std::endl;
	}
}
