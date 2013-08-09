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

//TODO make the overloaded functions templated
::std::vector< std::string>
operator - (::std::vector< ::std::string>& lhs, ::std::vector< ::std::string>& rhs);

::std::vector< std::string>&
operator + (::std::vector< ::std::string>& lhs, const ::std::vector< ::std::string>& rhs);

::std::ostream&
operator << (::std::ostream& os, const ::std::vector< ::std::string>& input);

::std::ostream&
operator << (::std::ostream& os, const ::std::vector< ::std::pair< ::std::string, ::std::string > >& input);

class RandomNumberGenerator
{
	public:
		RandomNumberGenerator();

		float randFloat( float min, float max);

		int randInt( int min, int max);

	private:

		::boost::mt19937 rng;

};


//transpose for vectors
#endif /* UTILITIES_H_ */
