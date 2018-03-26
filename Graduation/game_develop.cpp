
#include "bunny_class.hpp"
#include "game_init.hpp"
#include <chrono>
#include <thread>
#include <stdio.h>
#include "game_develop.hpp"
#include <stack>


bunny bunnyReproduce(bunny& female){
	bunny child;
	child.setColour(female.getColour());
	return child;
}

int game_develop(){

	std::list<bunny> listOfBunny{};
	std::list<bunny> temp_list{};
	std::vector<bunny> femaleBunnies;

	for(int i=0;i<5;i++){
		listOfBunny.push_back(bunny());
	}


	int turn{0};

	while(turn++<150){	//10 turns

		int numberOfMales{0};		//clear the number of males and female bunnies capable of reproduction
		femaleBunnies.clear();

		for(auto it=listOfBunny.begin();it!=listOfBunny.end();it++){	//loop the list of bunnies
			it->print();
			it->grow();

			if(it->getAge() == 10 && (it->evilBunny()==false)){
					//delete *it;
				it=listOfBunny.erase(it);		//point the iterator to the list element in front of the one we deleted.
			}
			else if(it->getAge() == 50 && (it->evilBunny())){
				it=listOfBunny.erase(it);		//point the iterator to the list element in front of the one we deleted.
			}

			if (it->getAge()>=2 && it->getSex()=="Female" && (it->evilBunny()==false)){	//Put the females in a stack for coitus.
				femaleBunnies.push_back(*it);		//	!CAREFUL! Push_back makes a copy. Declare a copy constructor for the class.
													//std::cout<<"Females size: "<<femaleBunnies.size()<<std::endl;
			}
			else if(it->getAge()>=2 && it->getSex()=="Male" && (it->evilBunny()==false))
				numberOfMales++;		//each turn this resets.
										//std::cout<<"males: "<<numberOfMales<<std::endl;
		}

		for (int j=0;j<numberOfMales;j++){
			for (int i=0;i<femaleBunnies.size();i++){
				femaleBunnies[i].print();
				bunny child=bunnyReproduce(femaleBunnies[i]);
				temp_list.push_back(child);
			}
		}

	}
	listOfBunny.splice(temp_list.end(), temp_list);	//append the temp list to the main bunnies list.

	return 0;

}

