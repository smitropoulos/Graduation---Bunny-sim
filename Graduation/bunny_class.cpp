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

bunny::bunny():m_sex(sex[randomIntGen(0, uint(sex.size())-1)]),m_colour(colours[randomIntGen(0, uint(colours.size())-1)]),m_age(0){
	if (m_sex=="Male"){
		m_name =bunnyNamesMale[randomIntGen(0, uint(bunnyNamesMale.size())-1)];
		m_sprite='m';
	}
	else if( m_sex=="Female"){
		m_name =bunnyNamesFemale[randomIntGen(0, uint(bunnyNamesFemale.size())-1)];
		m_sprite='f';
	}
	if(randomIntGen(0,10) >= 8){    //condition ? resultm_ifm_true : resultm_ifm_false
		m_radioactive_mutant_vampire_bunny = true;
		m_sprite='X';
	}
}

bunny::bunny(const bunny& other){
	m_age=other.m_age;
	m_sex=other.m_sex;
	m_colour=other.m_colour;
	m_name=other.m_name;
	m_sprite=other.m_sprite;
	m_radioactive_mutant_vampire_bunny=other.m_radioactive_mutant_vampire_bunny;
	m_position=other.m_position;
}

bunny::~bunny(){}


	///================================== Getters setters ==================================

unsigned int bunny::getAge(){
	return m_age;
}
std::string bunny::getSex(){
	return m_sex;
}

bool bunny::evilBunny(){
	return m_radioactive_mutant_vampire_bunny;
}

void bunny::setColour(std::string colour){
	m_colour=colour;
}

std::string bunny::getColour(){
	return m_colour;
}

std::pair<int, int>  bunny::getPosition(){
	return m_position;
}

void bunny::setPosition(int X, int Y){
	m_position.first=X;
	m_position.second=Y;
}

void bunny::setPosition(std::pair<int, int> pos){
	m_position.first=pos.first;
	m_position.second=pos.second;
}

char bunny::getSprite(){
	return m_sprite;
}

	///================================== methods ==================================


void bunny::print(){
	std::cout<<m_sex<<" Bunny "<<m_name<<" of colour "<<m_colour<<" at age "<<m_age<<std::endl;
}

void bunny::grow(){
	m_age++;
}

void bunny::updateSprite(){
	if(this->evilBunny()){
		m_sprite='X';
	}
	else if(m_age>1 && m_sex=="Male"){
		m_sprite='M';
	}
	else if(m_age>1 && m_sex=="Male"){
		m_sprite='F';
	}
}

void bunny::infectBunny (bunny& poorBunny){
	if (poorBunny.evilBunny()==false)
		poorBunny.m_radioactive_mutant_vampire_bunny=true;
}
