
#include "bunny_class.hpp"
#include "game_init.hpp"
#include <chrono>
#include <thread>
#include <stdio.h>
#include "game_develop.hpp"
#include <stack>


bunny coitusProduct(bunny& female){
	bunny *child=new bunny();
	child->setColour(female.getColour());
	return *child;
}


int game_develop(){

	std::list<bunny> list=game_init();
	std::vector<bunny> femaleBunnies;
	int turn{0};

	while(turn++<10){	//10 turns

		int numberOfMales{0};

		for(auto it=list.begin();it!=list.end();it++){	//loop the list of bunnies
			it->print();
			it->grow();
			if(it->getAge() == 10){
				it=list.erase(it);		//point the iterator to the list element in front of the one we deleted.
			}

			if (it->getAge()>=2 && it->getSex()=="Female" && (it->evilBunny()==false)){	//Put the females in a stack for coitus.
				femaleBunnies.push_back(*it);		//	!CAREFUL! Push_back makes a copy. Declare a copy constructor for the class.
				//std::cout<<"Females size: "<<femaleBunnies.size()<<std::endl;
			}
			else if(it->getAge()>=2 && it->getSex()=="Male" && (it->evilBunny()==false))
				numberOfMales++;		//each turn this resets.
			//std::cout<<"males: "<<numberOfMales<<std::endl;
		}

		for (numberOfMales;numberOfMales>0;numberOfMales--){
			for (unsigned long i=femaleBunnies.size();i>0;i--){
				bunny child=coitusProduct(femaleBunnies[i]);

				list.push_back(child);
			}
		}
		femaleBunnies.clear();
		
	}



	std::cout<<list.size()<<std::endl;


	return 0;

}

