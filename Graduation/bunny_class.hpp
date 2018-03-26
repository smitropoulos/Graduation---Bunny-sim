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
	int m_age{0};
	std::string m_name{};
	bool m_radioactive_mutant_vampire_bunny{};
public:
	bunny();
	bunny(const bunny& other);
	bunny(const bunny& mom,int n);
	~bunny();

	void print();
	void grow();
	unsigned int getAge();
	std::string getSex();
	bool evilBunny();
	void setColour(std::string colour);
	std::string getColour();

};

#endif /* bunny_classm_hpp */
