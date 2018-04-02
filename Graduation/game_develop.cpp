
#include "bunny_class.hpp"
#include <chrono>
#include <thread>
#include <stdio.h>
#include "game_develop.hpp"
#include <stack>
#include <algorithm>
#include "grid.hpp"
#include <set>
#include <list>

	///TO-DO LIST
	//add back to the set of pairs when a bunny is erased.

	//needed to manage other threads
std::mutex cinMutex;
std::atomic_bool cull;

	//Grid size
int const gridX=80;
int const gridY=80;

int turn=0;
int delay=1; //1 second

	//reduce the population of bunnies on demand flag
void theCullingOnDemand()
{//to be ran on a seperate thread
	while(1){
		char ss;
		if(turn==10)
			break;
		std::lock_guard<std::mutex> lock(cinMutex);
		ss=std::cin.get();
		if (ss=='k')
			cull=true;
	}
}

	//the bunnies reproduce..naturally..
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
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));		//Wait a second between announcements.
	return child;
}

	//return a random pair of position integers for the grid.
std::set<std::pair<int, int> > & initPositionSet(){
		//construct a set of all the possible positions the bunnies can take on the grid.
	std::set<std::pair<int, int> > static freePositionsSet;
	std::pair<int, int> k;

	for (int i=0;i<gridY;i++){
		for (int j=0;j<gridX;j++){
			k.first=i;
			k.second=j;
			freePositionsSet.insert(k);
		}
	}
	return freePositionsSet;
}


	//update bunny position with a valid move
int randomBunnyMove (std::set<std::pair<int, int>>& freePositionsSet,bunny& bun){
		///find and pop,else try random move
	while(1 && freePositionsSet.size()!=0){

		auto setBegin=freePositionsSet.begin();
		advance(setBegin,randomIntGen(0, freePositionsSet.size()));		//advancing the position of the iterator to a random element inside the set
		bun.setPosition(*setBegin);
		freePositionsSet.erase(*setBegin);
		return 0;

	}
	return -1;
}



	//Population control method
void theCulling(std::list<bunny>& listOfBunnies, int limit,std::set<std::pair<int, int> >&  freePositionsSet){

	for (int j=0;j<limit;j++){
		std::list<bunny>::iterator i=listOfBunnies.begin();
		int in=randomIntGen(0, listOfBunnies.size()-1);
		std::advance(i,in);
		freePositionsSet.insert(i->getPosition());		//return the position of this bunny to be erased to the set of positions
		listOfBunnies.erase(i);
	}
}


	////////////////#########################Main Method################################?????????

int game_develop(unsigned int turns){

	std::list<bunny> listOfBunny{};
	std::vector<bunny> femaleBunnies{};
	auto grid = initGrid(gridX, gridY);
	auto positionList = initPositionSet();

		// Initial bunnies!
	for(int i=0;i<5;i++){
		bunny bun;
		randomBunnyMove(positionList,bun);
		listOfBunny.push_back(bun);
	}


	std::thread charGetter(theCullingOnDemand);

	for(;turn<turns;turn++){    //10 turns minimum to test for deaths!

		int numberOfMales{0};        //clear the number of males and female bunnies capable of reproduction
		femaleBunnies.clear();


		for(auto it=--listOfBunny.end();it!=--listOfBunny.begin();--it){    //loop the list of bunnies

				//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				//it->print();        //Debugging

			it->grow();
			it->updateSprite();											//update the sprite for the bunny
			updateGrid(grid, it->getPosition(),it->getSprite());		//update the grid point with the appropriate value


				///=======================================start of list loop========================================

			if (it->evilBunny()==false ){
				if(it->getAge() == 10){
					std::cout<<"Aw, a bunny died!"<<std::flush;
					it->print();
					positionList.insert(it->getPosition());	//return the position of this bunny to be erased to the set of positions
					it=listOfBunny.erase(it);        //point the iterator to the list element in front of the one we deleted.

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
					positionList.insert(it->getPosition());	//return the position of this bunny to be erased to the set of positions
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
				continue;
			}
		}//for



			///=======================================Pop control========================================

		for (int j=0;j<numberOfMales;j++){
			if(cull)	//check if a culling is in order!
				break;
			for (int i=0;i<femaleBunnies.size();i++){
				if(cull)	//check if a culling is in order!
					break;
				bunny child=bunnyReproduce(femaleBunnies[i]);
				randomBunnyMove(positionList,child);		//update child's position with a random move
				listOfBunny.push_back(child);

					//Auto culling!
				if (listOfBunny.size()>=1000){
					theCulling(listOfBunny, listOfBunny.size()/2, positionList);
				}
			}
		}

		if(cull){
			theCulling(listOfBunny, listOfBunny.size()/2, positionList);
			std::cout<<"A CULLING HAS BEEN ORDERED!\n Bunny population is "<<listOfBunny.size()<<std::endl;
			cull=false;
		}
		std::cout<<"\n####################END OF TURN "<<turn+1<<"########################\n"<<std::endl;

		printGrid(grid);
		std::this_thread::sleep_for(std::chrono::milliseconds(2*delay));
		

	}//for turns
	std::cout<<"Press a button to exit"<<std::endl;
	charGetter.join();
	return 0;
}//main

