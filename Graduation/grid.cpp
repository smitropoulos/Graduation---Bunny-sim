	//
	//  grid.cpp
	//  Graduation
	//
	//  Created by Stefanos Mitropoulos on 31/03/2018.
	//  Copyright © 2018 Stefanos Mitropoulos. All rights reserved.
	//

#include "grid.hpp"
#include "bunny_class.hpp"
#include <iostream>
#include <set>

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

std::vector<char> neighbours(bunny& bun,std::set<std::pair<int, int>> gridPositions,int gridX, int gridY){

	std::vector<char> takenPositions{};
		//In case the bunny is next to a border or an O position is not in the list of free moves, a move is automatically blocked.
/*
 		X
 	_________
	|___O___|
Y	O___k___O
	|___O___|

Using this we can determine what we need to check
*/


	if ( bun.getPosition().first ==0 || gridPositions.find({bun.getPosition().first-1,bun.getPosition().second})!=gridPositions.end()){
		takenPositions.push_back('l');
	}
	if ( bun.getPosition().first ==gridX || gridPositions.find({bun.getPosition().first+1,bun.getPosition().second})!=gridPositions.end()){
		takenPositions.push_back('r');
	}
	if ( bun.getPosition().second ==0 || gridPositions.find({bun.getPosition().first,bun.getPosition().second-1})!=gridPositions.end()){
		takenPositions.push_back('u');
	}
	if ( bun.getPosition().second ==gridY || gridPositions.find({bun.getPosition().first,bun.getPosition().second+1})!=gridPositions.end()){
		takenPositions.push_back('d');
	}

	return takenPositions;


}
