
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
	if (!child.evilBunny()){
		std::cout<<"Aah! Newborn "<<std::flush;
		child.print();
	}else{
		std::cout<<"THE DEVIL! "<<std::flush;
		child.print();
	}
	return child;
}

void theCulling(std::list<bunny>& listOfBunnies){
		//TO-DO FIND A WAY TO SHUFFLE.
		//ITERATE BACKWARDS TO GET RID OF THE TEMP LIST!!
		//std::random_shuffle(listOfBunnies.begin(), listOfBunnies.end());
	
}

int game_develop(){
	
	std::list<bunny> listOfBunny{};
	std::vector<bunny> femaleBunnies;
	
	for(int i=0;i<5;i++){
		listOfBunny.push_back(bunny());
	}
	
	
	int turn{0};
	
	while(turn++<10){	//10 turns
		
		int numberOfMales{0};		//clear the number of males and female bunnies capable of reproduction
		femaleBunnies.clear();
		
		
		for(auto it=--listOfBunny.end();it!=--listOfBunny.begin();--it){	//loop the list of bunnies
			it->grow();
			it->print();

			if (it->evilBunny()==false){
				if(it->getAge() == 10){
					it=listOfBunny.erase(it);		//point the iterator to the list element in front of the one we deleted.
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
				it=listOfBunny.erase(it);		//point the iterator to the list element in front of the one we deleted.
			}

			for (int j=0;j<numberOfMales;j++){
				for (int i=0;i<femaleBunnies.size();i++){
					femaleBunnies[i].print();
					bunny child=bunnyReproduce(femaleBunnies[i]);
					listOfBunny.push_back(child);
				}
			}
		}
	}
	return 0;

}

