	//
	//  game_develop.cpp
	//  Graduation
	//
	//  Created by Stefanos Mitropoulos on 26/03/2018.
	//  Copyright © 2018 Stefanos Mitropoulos. All rights reserved.
	//
#include "bunny_class.hpp"
#include "game_init.hpp"
#include <chrono>
#include <thread>
#include <stdio.h>
#include "game_develop.hpp"

bunny coitusProduct(const bunny& male,const bunny& female){
	return 
}


int game_develop(){

	std::list<bunny> list=game_init();
	std::list<bunny> femaleBunnies;

	while (list.size()>0){
		list.size();
		int numberOfMales{0};
		int numberOfFemales{0};

		for(std::list<bunny>::iterator it=list.begin();it!=list.end();it++){
			it->grow();
			if(it->getAge() > 3){
				it=list.erase(it);		//point the iterator to the list element in front of the one we deleted.
			}

				//Check if there are enough bunnies to have coitus, ^^
			if(it->getSex()=="Male" && it->getAge()>=2){
				numberOfMales++;
			}
			else if (it->getSex()=="Female" && it->getAge()>=2){
				numberOfFemales++;
				femaleBunnies.push_back(*it);
			}


			
				std::cout<<femaleBunnies.size()<<std::endl;

		}
		
	}
	return 0;
}

