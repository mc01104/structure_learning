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
		typedef ::std::vector< ::std::pair< ::std::string, ::std::string> > Edges;

		public:
			Problem();

			virtual ~Problem();

			friend ::std::ostream& operator<< (::std::ostream& os, const Problem& problem);

			void setPathtoGraph( const ::std::string& path) { this->pathToGraph = path;};

			void setPathtoData( const ::std::string& path) { this->pathToData = path;};

			void setNodeOrdering( const ::std::vector< ::std::string>& nodeOrdering) {this->nodeOrdering = nodeOrdering;};

			void setRequiredEdges( const Edges& requiredEdges) {this->requiredEdges = requiredEdges;};

			void setProhibitedEdges( const Edges& prohibitedEdges) {this->prohibitedEdges = prohibitedEdges;};

			const ::std::string& getPathToData() const { return this->pathToData;};

			const ::std::string& getPathToGraph() const { return this->pathToGraph;};

			const ::std::vector< ::std::string>& getNodeOrdering() const {return this->nodeOrdering;};

			const Edges& getRequiredEdges() const { return this->requiredEdges;};

			const Edges& getProhibitedEdges() const { return this->prohibitedEdges;};

		private:

			::std::string pathToGraph;

			::std::string pathToData;

			::std::vector< ::std::string> nodeOrdering;

			Edges requiredEdges;

			Edges prohibitedEdges;
	};

} /* namespace sl */
#endif /* PROBLEM_H_ */
