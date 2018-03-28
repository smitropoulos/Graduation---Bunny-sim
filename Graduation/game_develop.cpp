
#include "bunny_class.hpp"
#include "game_init.hpp"
#include <chrono>
#include <thread>
#include <stdio.h>
#include "game_develop.hpp"
#include <stack>
#include <algorithm>


bunny bunnyReproduce(bunny& female){
	bunny child;
	child.setColour(female.getColour());
	if (!child.evilBunny()){
		std::cout<<"Aah! Newborn "<<std::flush;
		child.print();
	}else{
		std::cout<<"THE DEVIL! "<<std::flush;
		child.print();
	}
	return child;
}

void theCulling(std::vector<bunny>& listOfBunnies){
		//TO-DO seed the engine once

		std::random_shuffle(listOfBunnies.begin(), listOfBunnies.end());
	
}

int game_develop(unsigned int turns){
	
	std::vector<bunny> listOfBunny{};
	std::vector<bunny> femaleBunnies;
	
	for(int i=0;i<5;i++){
		listOfBunny.push_back(bunny());
	}
	
		
	for(int turn=0;turn<turns;turn++){	//10 turns
		
		int numberOfMales{0};		//clear the number of males and female bunnies capable of reproduction
		femaleBunnies.clear();
		
		
		for(auto it=--listOfBunny.end();it!=--listOfBunny.begin();--it){	//loop the list of bunnies
			it->grow();
			//it->print();

			if (it->evilBunny()==false){
				if(it->getAge() == 10){
					it=listOfBunny.erase(it);		//point the iterator to the list element in front of the one we deleted.
					std::cout<<"Aw, a bunny died!"<<std::flush;
					it->print();
				}
				else if(it->getAge()>=2 && it->getSex()=="Female")
					{
					femaleBunnies.push_back(*it);		//	!CAREFUL! Push_back makes a copy. Declare a copy constructor for the class.
														//std::cout<<"Females size: "<<femaleBunnies.size()<<std::endl;
					}
				else if(it->getAge()>=2 && it->getSex()=="Male")
					{
					numberOfMales++;		//each turn this resets.
											//std::cout<<"males: "<<numberOfMales<<std::endl;
					}
			}
			else{
				if (it->getAge() == 50){
				it=listOfBunny.erase(it);		//point the iterator to the list element in front of the one we deleted.
				std::cout<<"Thank God!A radioactive mutant vampire bunny died!"<<std::flush;
				it->print();
			}
			}
			for (int j=0;j<numberOfMales;j++){
				for (int i=0;i<femaleBunnies.size();i++){
					femaleBunnies[i].print();
					bunny child=bunnyReproduce(femaleBunnies[i]);
					listOfBunny.push_back(child);
				}//for
			}//for
		}//for list
	}//for	turns
	return 0;

}//main

