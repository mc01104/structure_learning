/*
 * Solver.h
 *
 *  Created on: 17 Jan 2013
 *      Author: george
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "../Network.h"
#include "../Problem.h"

namespace sl
{
	class Solution;

	class Solver
	{
		public:
			Solver();

			virtual ~Solver();

			virtual void initialize( const Problem& prob);

			virtual void run() = 0;

			Solution* getSolution() const {return this->solution;};

			void setMaxIter(int iter) {this->maxIter = iter;} ;

			int getMaxIter() const {return this->maxIter;};

		protected:
			Problem problem;

			Solution* solution;

			int maxIter;

			Network* net;

			void loadData();

			void loadGraph();
	};

} /* namespace sl */
#endif /* SOLVER_H_ */
