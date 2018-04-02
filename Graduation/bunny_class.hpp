	//
	//  bunnym_class.hpp
	//  Graduation
	//
	//  Created by Stefanos Mitropoulos on 26/03/2018.
	//  Copyright © 2018 Stefanos Mitropoulos. All rights reserved.
	//

#ifndef bunny_classm_hpp
#define bunny_classm_hpp

#include <stdio.h>
#include <iostream>
#include <random>
#include "random_gen.hpp"

class bunny
{
private:

	std::string m_sex{};
	std::string m_colour{};
	std::string m_name{};

	char m_sprite{};

	int m_age{0};

	bool m_radioactive_mutant_vampire_bunny{false};

	std::pair<int, int> m_position{};
public:
	bunny();
	bunny(const bunny& other);
	~bunny();

		///==================================setters getters ==================================
	bool evilBunny();
	std::string getSex();
	unsigned int getAge();
	std::string getColour();
	std::pair<int, int>  getPosition();
	char getSprite();

	void setColour(std::string colour);
	void setPosition(int X,int Y);
	void setPosition(std::pair<int, int> pos);
	
		///==============================Methods===========================


	void infectBunny (bunny& poorBunny);
	void print();
	void grow();
	void updateSprite();


};

#endif /* bunny_classm_hpp */
