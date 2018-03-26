//
//  random_gen.cpp
//  Graduation
//
//  Created by Stefanos Mitropoulos on 26/03/2018.
//  Copyright © 2018 Stefanos Mitropoulos. All rights reserved.
//

#include "random_gen.hpp"
#include <random>
#include <iostream>

int randomIntGen(int bot, int top){

std::random_device rd;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<> dis(bot, top);
return dis(gen);

}
