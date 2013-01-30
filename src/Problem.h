/*
 * Problem.h
 *
 *  Created on: 17 Jan 2013
 *      Author: george
 */

#ifndef PROBLEM_H_
#define PROBLEM_H_

#include <string>
#include <vector>

namespace sl
{

	class Problem
	{
		public:
			Problem();

			Problem(const ::std::string& pathToData,
					 const ::std::string& pathToGraph,
					 const ::std::vector< ::std::string>& nodeOrdering,
					 const ::std::vector< ::std::string>& solvers);

			virtual ~Problem();

			friend ::std::ostream& operator<< (::std::ostream& os, const Problem& problem);

		private:
			::std::string pathToGraph;
			::std::string pathToData;
			::std::vector< ::std::string> nodeOrdering;
			::std::vector< ::std::string> solvers;
	};

} /* namespace sl */
#endif /* PROBLEM_H_ */
