	//
	//  game_init.cpp
	//  Graduation
	//
	//  Created by Stefanos Mitropoulos on 26/03/2018.
	//  Copyright © 2018 Stefanos Mitropoulos. All rights reserved.
	//

#include "game_init.hpp"

std::list<bunny> game_init(){
	
	std::list<bunny> listOfBunny;

	// Create a bunny list for the begining of the game.

	for(int i=0;i<5;i++){
		bunny bi;
		listOfBunny.push_back(bi);
		listOfBunny.size();
	}
	return listOfBunny;
}
