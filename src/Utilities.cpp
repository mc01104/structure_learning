/*
 * Utilities.cpp
 *
 *  Created on: 15 Feb 2013
 *      Author: george
 */

#include "Utilities.h"

#include <boost/random.hpp>
#include <ctime>


::std::vector< std::string>&
operator - (::std::vector< ::std::string>& lhs, const ::std::vector< ::std::string>& rhs)
{
	for(::std::vector< ::std::string>::iterator it = lhs.begin(); it != lhs.end(); ++it)
	{
		if ( ::std::find(rhs.begin(), rhs.end(), *it) != rhs.end())
					lhs.erase(it);

	}

	return lhs;
}

::std::vector< ::std::string>&
 operator + (::std::vector< ::std::string>& lhs, const ::std::vector< ::std::string>& rhs)
{

	for(::std::vector< ::std::string>::const_iterator it = rhs.begin(); it != rhs.end(); ++it)
	{
		if ( ::std::find(lhs.begin(), lhs.end(), *it) == lhs.end())
					lhs.push_back(*it);

	}
	return lhs;
}

int
generateRandomInt (const int& min, const int& max)
{

	//srand(::std::time(0));
	return min + rand() % (max - min);
}

float
generateRandomFloat(float min, float max)
{
	srand(::std::time(0));
	return  min + (float)rand()/((float)RAND_MAX/(max-min));
}

RandomNumberGenerator::RandomNumberGenerator() {
	rng.seed(::std::time(0));
}

float
RandomNumberGenerator::randFloat(float min, float max)
{
	::boost::uniform_real<> gen(min,max);

	::boost::variate_generator< ::boost::mt19937&, ::boost::uniform_real<> > numberGenerator(rng,gen);

	return numberGenerator();
}

int
RandomNumberGenerator::randInt(int min, int max)
{
	::boost::uniform_int<> gen(min,max);

	::boost::variate_generator< ::boost::mt19937&, ::boost::uniform_int<> > numberGenerator(rng,gen);

	return numberGenerator();
}



