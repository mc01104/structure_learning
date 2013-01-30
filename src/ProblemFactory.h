/*
 * ProblemFactory.h
 *
 *  Created on: 17 Jan 2013
 *      Author: george
 */

#ifndef PROBLEMFACTORY_H_
#define PROBLEMFACTORY_H_

#include <string>

namespace sl
{

	class Problem;

	class ProblemFactory
	{
		public:
			static ProblemFactory* getInstance();

			virtual ~ProblemFactory();

			Problem* create(const ::std::string& xmlString);

			void	destroy(Problem* problem);

		private:
			ProblemFactory();

			ProblemFactory(const ProblemFactory& pFactory);

			void operator=(const ProblemFactory&);

			static ProblemFactory* instance;
	};

} /* namespace sl */
#endif /* PROBLEMFACTORY_H_ */
