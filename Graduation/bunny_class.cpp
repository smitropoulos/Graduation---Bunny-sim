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
	}
	else if( m_sex=="Female"){
		m_name =bunnyNamesFemale[randomIntGen(0, uint(bunnyNamesFemale.size())-1)];
	}
	m_radioactive_mutant_vampire_bunny = randomIntGen(0,10) >= 8 ? true : false;	//condition ? resultm_ifm_true : resultm_ifm_false

}

bunny::bunny(const bunny& other){
	m_age=other.m_age;
	m_sex=other.m_sex;
	m_colour=other.m_colour;
	m_name=other.m_name;
	m_radioactive_mutant_vampire_bunny=other.m_radioactive_mutant_vampire_bunny;
}

void bunny::print(){
	std::cout<<m_sex<<" Bunny "<<m_name<<" of colour "<<m_colour<<" at age "<<m_age<<std::endl;
}

void bunny::grow(){
	m_age++;
}
unsigned int bunny::getAge(){
	return m_age;
}
std::string bunny::getSex(){
	return m_sex;
}

bunny::~bunny(){}

bool bunny::evilBunny(){
	return m_radioactive_mutant_vampire_bunny;
}

void bunny::setColour(std::string colour){
	m_colour=colour;
}

std::string bunny::getColour(){
	return m_colour;
}
