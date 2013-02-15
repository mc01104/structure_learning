/*
 * Problem.cpp
 *
 *  Created on: 17 Jan 2013
 *      Author: george
 */

#include "Problem.h"
#include <iostream>

namespace sl
{

	Problem::Problem() :
			pathToGraph(""),
			pathToData(""),
			nodeOrdering()
	{

	}


	Problem::~Problem()
	{

	}

	::std::ostream&
	operator <<(::std::ostream& os, const Problem& problem)
	{
		os << "overloading to print out the problem setting" << ::std::endl;
		os << "Path to Data :" << problem.pathToData << ::std::endl;
		os << "Path to Network (used as prior info):" << problem.pathToGraph << ::std::endl;
		os << "Node Ordering given by user:" << ::std::endl;
		for(::std::vector< ::std::string>::const_iterator it = problem.nodeOrdering.begin(); it != problem.nodeOrdering.end() - 1; ++it)
			os << *it << " =>";
		os << *(problem.nodeOrdering.end() - 1) << ::std::endl;

		os << ::std::endl;
		os << "Required Edges" << ::std::endl;
		for( Problem::Edges::const_iterator it = problem.requiredEdges.begin(); it != problem.requiredEdges.end(); ++it)
			os << it->first << " =>" << it->second << ::std::endl;

		os << ::std::endl << ::std::cout << "Prohibited Edges" << ::std::endl;

		for( Problem::Edges::const_iterator it = problem.prohibitedEdges.begin(); it != problem.prohibitedEdges.end(); ++it)
			os << it->first << " =>" << it->second << ::std::endl;


		return os;
	}
} /* namespace sl */
