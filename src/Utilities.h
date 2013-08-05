/*
 * Utilities.h
 *
 *  Created on: 15 Feb 2013
 *      Author: george
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <boost/random.hpp>

#include <string>
#include <vector>

::std::vector< std::string>&
operator - (::std::vector< ::std::string>& lhs, const ::std::vector< ::std::string>& rhs);

::std::vector< std::string>&
operator + (::std::vector< ::std::string>& lhs, const ::std::vector< ::std::string>& rhs);

class RandomNumberGenerator
{
	public:
		RandomNumberGenerator();

		float randFloat( float min, float max);

		int randInt( int min, int max);

	private:

		::boost::mt19937 rng;

};

int generateRandomInt (const int& min, const int& max);

float generateRandomFloat(float min, float max);

//transpose for vectors
#endif /* UTILITIES_H_ */
