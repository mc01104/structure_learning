/*
 * SolverFactory.cpp
 *
 *  Created on: 15 Feb 2013
 *      Author: george
 */

#include "SolverFactory.h"
#include "SolverDefs.h"

#include <tinyxml.h>
#include <string>

namespace sl
{
	SolverFactory* SolverFactory::instance = NULL;

	SolverFactory::SolverFactory()
	{

	}

	SolverFactory::~SolverFactory()
	{

	}

	SolverFactory::SolverFactory(const SolverFactory& sFactory)
	{

	}

	SolverFactory*
	SolverFactory::getInstance()
	{
		if(!instance)
			instance = new SolverFactory();

		return instance;
	}

	::std::vector< Solver*>
	SolverFactory::create(const ::std::string& xmlString)
	{
		TiXmlDocument doc( xmlString );
		doc.LoadFile();

		TiXmlHandle hDoc(&doc);
		TiXmlElement *pRoot, *pnext;

		pRoot = doc.FirstChildElement("Problem");

		::std::vector< Solver*> solvers;

	    if(pRoot)
	    {
	        //Load the solvers
	        pnext = pRoot->FirstChildElement("Solvers");
	        if(pnext)
	        {
	            for(TiXmlElement* p = pnext->FirstChildElement("Item"); p; p = p->NextSiblingElement())
	            {
	            	::std::string type = p->Attribute("type");

	            	::std::string iter_string = p->Attribute("maxIter");

	            	int iterations = 100;

	            	if(iter_string.c_str())
	            		iterations = atoi(iter_string.c_str());

	            	if(type == "GREEDY")
	            	{
	            		Solver* solver = new GreedySolver();
	            		solver->setMaxIter(iterations);
	            		solvers.push_back(solver);
	            	}

	            }
	        }

	    }

	    return solvers;
	}

	void
	SolverFactory::destroy(Solver* solver)
	{
		delete(solver);
	}

} /* namespace sl */
