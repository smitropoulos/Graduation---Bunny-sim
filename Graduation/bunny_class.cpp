//
//  bunny_class.cpp
//  Graduation
//
//  Created by Stefanos Mitropoulos on 26/03/2018.
//  Copyright © 2018 Stefanos Mitropoulos. All rights reserved.
//

#include "bunny_class.hpp"
#include <random>
#include <iostream>
#include <vector>

//In order to use operators such as size(), we need container classes such as vectors.
std::vector<std::string> bunnyNamesMale{"Oreo", "Thumper", "Peanut", "Nibbles","Smokey", "Buddy"};
std::vector<std::string> bunnyNamesFemale{"Isabelle","Lillie","Snowball", "Bella","Baby","Daisy",};
std::vector<std::string> colours{"White","Brown","Black","Spotted"};
std::vector<std::string> sex{"Male","Female"};

//remember, size() returns the base 1 size e.g. [0,1,2]size() =3 but there is no 3rd element!

bunny::bunny():_sex(sex[randomIntGen(0, uint(sex.size())-1)]),_colour(colours[randomIntGen(0, uint(colours.size())-1)]),_age(0){
	if (_sex=="Male"){
		_name =bunnyNamesMale[randomIntGen(0, uint(bunnyNamesMale.size())-1)];
	}
	else if( _sex=="Female"){
		_name =bunnyNamesFemale[randomIntGen(0, uint(bunnyNamesFemale.size())-1)];
	}
	_radioactive_mutant_vampire_bunny = randomIntGen(0,10) >= 2 ? true : false;	//condition ? result_if_true : result_if_false

}

bunny::bunny(const bunny& other){
	_age=other._age;
	_sex=other._sex;
	_colour=other._colour;
	_name=other._name;
	_radioactive_mutant_vampire_bunny=other._radioactive_mutant_vampire_bunny;
}

void bunny::print(){
	std::cout<<_sex<<_name<<_colour<<_age<<std::endl;
}

void bunny::grow(){
	_age++;
}
unsigned int bunny::getAge(){
	return _age;
}
std::string bunny::getSex(){
	return _sex;
}

bunny::~bunny(){}

bool bunny::evilBunny(){
	return _radioactive_mutant_vampire_bunny;
}

void bunny::setColour(std::string colour){
	_colour=colour;
}

std::string bunny::getColour(){
	return _colour;
}
