/*
 * GreedySolver.h
 *
 *  Created on: 15 Feb 2013
 *      Author: george
 */

#ifndef GREEDYSOLVER_H_
#define GREEDYSOLVER_H_

#include "Solver.h"

namespace sl {

	class GreedySolver: public sl::Solver
	{
		public:
			GreedySolver();

			virtual ~GreedySolver();

			virtual void run();
	};

} /* namespace sl */
#endif /* GREEDYSOLVER_H_ */
