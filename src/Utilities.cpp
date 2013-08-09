/*
 * Utilities.cpp
 *
 *  Created on: 15 Feb 2013
 *      Author: george
 */

#include "Utilities.h"

#include <boost/random.hpp>
#include <ctime>


::std::vector< std::string>
operator - (::std::vector< ::std::string>& lhs, ::std::vector< ::std::string>& rhs)
{
	::std::vector< ::std::string> tmp(lhs);

	for(::std::vector< ::std::string>::iterator it = rhs.begin(); it != rhs.end(); ++it)
	{
		::std::vector < ::std::string>::iterator iter = ::std::find(tmp.begin(), tmp.end(), *it);
		if ( iter != tmp.end())
			tmp.erase(iter);
	}

	return tmp;
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

::std::ostream&
 operator << (::std::ostream& os, const ::std::vector< ::std::string>& input)
{
	for(::std::vector< ::std::string>::const_iterator it = input.begin(); it != input.end(); ++it)
		os << *it << "  ";
	os << ::std::endl;

	return os;
}

::std::ostream&
 operator << (::std::ostream& os, const ::std::vector< ::std::pair< ::std::string, ::std::string> >& input)
{
	::std::vector< ::std::pair< ::std::string, ::std::string> >::const_iterator it;
	for(it = input.begin(); it != input.end(); ++it)
		os << "first:" << it->first << "  second :" << it->second << ::std::endl;

	return os;
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



