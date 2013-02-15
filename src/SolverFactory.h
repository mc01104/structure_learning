/*
 * SolverFactory.h
 *
 *  Created on: 15 Feb 2013
 *      Author: george
 */

#ifndef SOLVERFACTORY_H_
#define SOLVERFACTORY_H_

#include <vector>
#include <string>

namespace sl {

	class Solver;

	class SolverFactory {
		public:

			static SolverFactory* getInstance();

			virtual ~SolverFactory();

			::std::vector< Solver*> create(const ::std::string& xmlString);

			void destroy( Solver* solver);

		private:

			SolverFactory();

			SolverFactory(const SolverFactory&);

			void operator=(const SolverFactory&);

			static SolverFactory* instance;

	};

} /* namespace sl */
#endif /* SOLVERFACTORY_H_ */
