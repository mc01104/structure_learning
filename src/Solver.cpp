/*
 * Solver.cpp
 *
 *  Created on: 17 Jan 2013
 *      Author: george
 */

#include "Solver.h"

namespace sl
{

	Solver::Solver():
			problem(),
			maxIter()
	{
	}


	Solver::~Solver()
	{
	}

	void
	Solver::initialize(const Problem& problem)
	{
		this->problem = problem;

		this->loadData();

		this->loadGraph();

	}

	void
	Solver::loadData()
	{

	}

	void
	Solver::loadGraph()
	{
		if(this->problem.getPathToGraph() != "")
			return;
	}

} /* namespace sl */
