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
			nodeOrdering(),
			solvers()
	{

	}

	Problem::Problem(const ::std::string& pathToData,
					   const ::std::string& pathToGraph,
					   const ::std::vector< ::std::string>& nodeOrdering,
					   const ::std::vector< ::std::string>& solvers)
	{
		this->pathToData = pathToData;
		this->pathToGraph = pathToGraph;
		this->nodeOrdering = nodeOrdering;
		this->solvers = solvers;
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

		os << "Solvers instantiated for the problem : " << ::std::endl;
		for(::std::vector< ::std::string>::const_iterator it = problem.solvers.begin(); it != problem.solvers.end(); ++it)
			os << *it << ::std::endl;

		return os;
	}
} /* namespace sl */
