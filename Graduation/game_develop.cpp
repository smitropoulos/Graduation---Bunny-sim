#include <set>
#include <list>
#include <chrono>
#include <thread>
#include <stack>
#include "bunny_class.hpp"
#include "game_develop.hpp"
#include "grid.hpp"


	///TO-DO LIST
//convert tehe available moves vector to std map
//add infect rules and mother next to child rules

	//needed in order to manage other threads
std::mutex cinMutex;
std::atomic_bool cull;

	//Grid size
int const gridX=80;
int const gridY=30;

bool printFlag=false;

int turn=0;
int delay=1000; //1 second default

int numberOfInitialBunnies=5;

void theCullingOnDemand(){
		//call the culling method on demand.
		//to be ran on a seperate thread
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

bunny bunnyReproduce(bunny& female){
	//the bunnies reproduce..naturally..
	//the new child bunny takes its mother's colour
	bunny child;
	child.setColour(female.getColour());
	if (!child.evilBunny()){
		if(printFlag){
		std::cout<<"Aah! Newborn "<<std::flush;
			child.print();}
	}else{
		if(printFlag){
		std::cout<<"THE DEVIL! "<<std::flush;
			child.print();}
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));		//Wait a second between announcements.
	return child;
}

std::set<std::pair<int, int>>& initPositionSet(){
		//construct a set of all the possible positions the bunnies can take on the grid. Returns a set	std::set<std::pair<int, int>>
	std::set<std::pair<int, int>> static freePositionsSet;
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


int randomBunnyPosition (std::set<std::pair<int, int>>& freePositionsSet,bunny& bun){
		//update bunny position with another valid position on the grid.

	while(1 && freePositionsSet.size()!=0){
		auto setBegin=freePositionsSet.begin();
		advance(setBegin,static_cast<unsigned int>(randomIntGen(0, static_cast<unsigned int>(freePositionsSet.size()))));		//advancing the position of the iterator to a random element inside the set. This way we cannot ever get outside the set's boundaries / improved performance by a lot.
		bun.setPosition(*setBegin);
		freePositionsSet.erase(*setBegin);
		return 0;
	}
	return -1;
}



void theCulling(std::list<bunny>& listOfBunnies, int limit,std::set<std::pair<int, int> >&  freePositionsSet){
		//reduce the population of bunnies on demand flag by interrupting the flow of the programme and halfing the bunnies.
		//Population control method
	for (int j=0;j<limit;j++){
		std::list<bunny>::iterator i=listOfBunnies.begin();
		int in=randomIntGen(0, static_cast<unsigned int>(listOfBunnies.size()-1));
		std::advance(i,in);
		freePositionsSet.insert(i->getPosition());		//return the position of this bunny to be erased to the set of positions
		listOfBunnies.erase(i);
	}
}


std::vector<char> availableMoves(bunny& bun,std::set<std::pair<int, int>> gridPositions,int gridX, int gridY){

		//returns the availble moves a bunny can make according to its neighbours and the borders of the board.
		//takes as parameters:
		//a bunny object
		//the set of gridPositions available
		//the grid dimensions, girdX and gridY

	std::vector<char> availableMoves{'d','l','r','u'};		//all the possible moves here.
															//In case the bunny is next to a border or an O position is not in the list of free moves, a move is automatically blocked.


	/*
	 X
	 _________
	 |___O___|
	 Y	 O___k___O
	 |___O___|

	 Using this we can determine what we need to check
	 */

		//If the bunny's position is either 0 or the bunny's position {(x-1),y} is taken, then left is not an option etc for the rest.

	if ( bun.getPosition().first == 0 || gridPositions.find({bun.getPosition().first-1,bun.getPosition().second})==gridPositions.end()){
		availableMoves.erase(find(availableMoves.begin(),availableMoves.end(),'l'));
	}
	if ( bun.getPosition().first == gridX || gridPositions.find({bun.getPosition().first+1,bun.getPosition().second})==gridPositions.end()){
		availableMoves.erase(find(availableMoves.begin(),availableMoves.end(),'r'));

	}
	if ( bun.getPosition().second == 0 || gridPositions.find({bun.getPosition().first,bun.getPosition().second-1})==gridPositions.end()){
		availableMoves.erase(find(availableMoves.begin(),availableMoves.end(),'u'));

	}
	if ( bun.getPosition().second == gridY || gridPositions.find({bun.getPosition().first,bun.getPosition().second+1})==gridPositions.end()){
		availableMoves.erase(find(availableMoves.begin(),availableMoves.end(),'d'));

	}

	//returns a vector containing the available moves of the bunny.
	//u for up
	//d for down etc

	return availableMoves;

}

int randomBunnyMovement(bunny& bun, std::vector<char>& availableMoves){

///Moves the bunny to its adjacent positions at random, if they are valid.

	auto randomMoveNumber=randomIntGen(0,static_cast<unsigned int>(availableMoves.size()));
	if (availableMoves.size()==0)
		return -1;

	auto bunnyMove = availableMoves[randomMoveNumber];

	switch (bunnyMove) {
		case 'l':
			bun.setPosition(bun.getPosition().first-1,bun.getPosition().second);
			break;
		case 'r':
			bun.setPosition(bun.getPosition().first+1,bun.getPosition().second);
			break;
		case 'u':
			bun.setPosition(bun.getPosition().first,bun.getPosition().second+1);
			break;
		case 'd':
			bun.setPosition(bun.getPosition().first,bun.getPosition().second-1);
			break;

	}
	return 0;
}



	////////////////######################### Main Method ################################////////////////

int game_develop(unsigned int turns){

	std::list<bunny> listOfBunny{};
	std::vector<bunny> femaleBunnies{};
	auto grid = initGrid(gridX, gridY);
	auto positionList = initPositionSet();

		// Initial bunnies!
	for(int i=0;i<numberOfInitialBunnies;i++){
		bunny bun;
		randomBunnyPosition(positionList,bun);	//make the bunnies take random-valid positions
		listOfBunny.push_back(bun);
	}


	std::thread charGetter(theCullingOnDemand);		//run a thread to manage the keypress events

	for(;turn<turns;turn++){    //10 turns minimum to test for deaths!

		int numberOfMales{0};        //clear the number of males and female bunnies capable of reproduction
		femaleBunnies.clear();


		for(auto it=--listOfBunny.end();it!=--listOfBunny.begin();--it){    //loop the list of bunnies


			it->grow();		//age the bunny
			it->updateSprite();		//update the sprite for the bunny

			positionList.insert(it->getPosition());	//return the position of this bunny to be erased to the set of positions
			updateGrid(grid, it->getPosition(),'.');	//paint the position of the bunny before the move to the default.

			auto availMoves = availableMoves(*it, positionList, gridX, gridY);
			randomBunnyMovement(*it,availMoves);
			updateGrid(grid, it->getPosition(),it->getSprite());		//update the grid point with the appropriate value
			positionList.erase(it->getPosition());	//erase the new position from the available positions list

				///=======================================start of list loop========================================

			if (it->evilBunny()==false ){
				if(it->getAge() == 10){
					if(printFlag){
					std::cout<<"Aw, a bunny died!"<<std::flush;
						it->print();}
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
					if(printFlag)
					std::cout<<"Thank God!A radioactive mutant vampire bunny died!"<<std::flush;
				}
				else{
						//Copy the iterator and try to increment it to finδ a non RMV bunny.
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
				randomBunnyPosition(positionList,child);		//update child's position with a new random position
				listOfBunny.push_back(child);

					//Auto culling!
				if (listOfBunny.size()>=1000){
					theCulling(listOfBunny, static_cast<unsigned int>(listOfBunny.size()/2), positionList);
				}
			}
		}

		if(cull){
			theCulling(listOfBunny, static_cast<unsigned int>(listOfBunny.size()/2), positionList);
			if(printFlag)
			std::cout<<"A CULLING HAS BEEN ORDERED!\n Bunny population is "<<listOfBunny.size()<<std::endl;
			cull=false;
		}
		//if(printFlag)
		std::cout<<"\n####################END OF TURN "<<turn+1<<"########################\n"<<std::endl;

		printGrid(grid);
		std::this_thread::sleep_for(std::chrono::milliseconds(2*delay));
		

	}//for turns
	std::cout<<"Press a button to exit"<<std::endl;
	charGetter.join();
	return 0;
}//main

