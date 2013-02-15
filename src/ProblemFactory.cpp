/*
 * ProblemFactory.cpp
 *
 *  Created on: 17 Jan 2013
 *      Author: george
 */

#include "ProblemFactory.h"
#include "Problem.h"
#include <string>
#include <vector>
#include <tinyxml.h>

namespace sl
{

	ProblemFactory* ProblemFactory::instance = NULL;

	ProblemFactory::ProblemFactory()
	{
	}

	ProblemFactory::~ProblemFactory()
	{
	}

	ProblemFactory* ProblemFactory::getInstance()
	{
		if(!instance)
			instance = new ProblemFactory();
		return instance;
	}

	Problem*
	ProblemFactory::create(const ::std::string& xmlString)
	{
		TiXmlDocument doc( xmlString );
		doc.LoadFile();

		TiXmlHandle hDoc(&doc);
	    TiXmlElement *pRoot, *pnext;
	    pRoot = doc.FirstChildElement("Problem");

	    ::std::string data_path ="", net_path = "";

	    ::std::vector< ::std::string> order, solvers;

	    if(pRoot)
	    {
	        //Get the path to the data
	        pnext = pRoot->FirstChildElement("Data");
	        data_path = pnext->Attribute("path");

	        //Path to prior Network
	        if(pRoot->FirstChildElement("Network"))
	        	net_path = pRoot->FirstChildElement("Network")->Attribute("path");

	        //Load the solvers
	        pnext = pRoot->FirstChildElement("Solvers");
	        if(pnext)
	        {
	            for(TiXmlElement* p = pnext->FirstChildElement("Item"); p; p = p->NextSiblingElement())
	               	solvers.push_back(p->Attribute("type"));
	        }

	        //Load the prior ordering
	        pnext = pRoot->FirstChildElement("Order");
	        if (pnext)
	        	for( TiXmlElement* p = pnext->FirstChildElement("Node"); p; p = p->NextSiblingElement())
	        		order.push_back(p->Attribute("name"));
	    }

	    //must also parse the document for required and prohibited edges

	    Problem* tmp = new Problem();

	    tmp->setPathtoData(data_path);

	    tmp->setPathtoGraph(net_path);

	    tmp->setNodeOrdering(order);

		return tmp;
	}

	void
	ProblemFactory::destroy(Problem* problem)
	{
		if(problem)
			delete(problem);
	}

} /* namespace sl */
