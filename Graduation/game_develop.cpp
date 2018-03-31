
#include "bunny_class.hpp"
#include "game_init.hpp"
#include <chrono>
#include <thread>
#include <stdio.h>
#include "game_develop.hpp"
#include <stack>
#include <algorithm>


std::mutex cinMutex;
int rounds;
std::atomic_bool cull;
int turn=0;


void theCullingOnDemand()
{
	while(turn<10){
		char ss;
		std::lock_guard<std::mutex> lock(cinMutex);
		ss=std::cin.get();
		if (ss=='k')
			cull=true;
	}
}

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
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));		//Wait a second between announcements.
	return child;
}

	//Population control method
void theCulling(std::list<bunny>& listOfBunnies, int limit){

	for (int j=0;j<limit;j++){
		std::list<bunny>::iterator i=listOfBunnies.begin();
		int in=randomIntGen(0, listOfBunnies.size()-1);
		std::advance(i,in);
		listOfBunnies.erase(i);
	}
}



int game_develop(unsigned int turns){

	std::list<bunny> listOfBunny{};
	std::vector<bunny> femaleBunnies{};

		// Initial bunnies!
	for(int i=0;i<5;i++){
		listOfBunny.push_back(bunny());
	}

	std::thread charGetter(theCullingOnDemand);

	for(turn;turn<turns;turn++){    //10 turns minimum to test for deaths!

		int numberOfMales{0};        //clear the number of males and female bunnies capable of reproduction
		femaleBunnies.clear();


		for(auto it=--listOfBunny.end();it!=--listOfBunny.begin();--it){    //loop the list of bunnies

				//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				//it->print();        //Debugging
			it->grow();


				///=======================================start of list loop========================================

			if (it->evilBunny()==false ){
				if(it->getAge() == 10){
					it=listOfBunny.erase(it);        //point the iterator to the list element in front of the one we deleted.
					std::cout<<"Aw, a bunny died!"<<std::flush;
					it->print();
				}
				else if(it->getAge()>=2 && it->getSex()=="Female")
					{
					femaleBunnies.push_back(*it);        //    !CAREFUL! Push_back makes a copy. Declare a copy constructor for the class.
														 //std::cout<<"Females size: "<<femaleBunnies.size()<<std::endl;
					}
				else if(it->getAge()>=2 && it->getSex()=="Male")
					{
					numberOfMales++;        //each turn this resets.
											//std::cout<<"males: "<<numberOfMales<<std::endl;
					}
			}
			else{
				if (it->getAge() == 50){
					it=listOfBunny.erase(it);        //point the iterator to the list element in front of the one we deleted.
					std::cout<<"Thank God!A radioactive mutant vampire bunny died!"<<std::flush;
				}
				else{
						//Copy the iterator and try to increment it to finf a non RMV bunny.
					auto tempiter = it;
					do{
						tempiter++;
					}while(tempiter->evilBunny()==false);
						//Infect the poor bunny!
					it->infectBunny(*tempiter);
				}
			}
			if(cull){
				cull=false;
				break;
			}
		}//for



			///=======================================Pop control========================================

		for (int j=0;j<numberOfMales;j++){
			for (int i=0;i<femaleBunnies.size();i++){
				bunny child=bunnyReproduce(femaleBunnies[i]);
				listOfBunny.push_back(child);

				if (listOfBunny.size()>=1000){
					theCulling(listOfBunny,listOfBunny.size()/2);
				}
			}
		}
		std::cout<<"####################END OF TURN "<<turn+1<<"########################"<<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	}//for turns

	return 0;
}//main

