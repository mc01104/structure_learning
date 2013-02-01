/*
 * Verifier.cpp
 *
 *  Created on: 23 Jan 2013
 *      Author: george
 */

#include "Verifier.h"

Verifier::Verifier() {
	// TODO Auto-generated constructor stub

}

Verifier::~Verifier() {
	// TODO Auto-generated destructor stub
}

bool
Verifier::isAcyclic(Network& graph)
{

	size_t numOfVertices = graph.getNumVertices();

	if( numOfVertices == 0)
	{
		std::cout << "0 vertices" << std::endl;
		return true;
	}

	std::cout << "1" << std::endl;

	Network::Vertex v;
	v = graph.findLeafNode();
	//std::cout << graph.getGraph()[v].name << std::endl;
	std::cout << "2" << std::endl;
	if(v)
	{
		std::cout << "3" << std::endl;
//		graph.removeVertex(v);
		std::cout << "4" << std::endl;
		return this->isAcyclic(graph);
	}
//	else
//	{
//		std::cout << "5" << std::endl;
//		return false;
//	}
	return true;
}

//	Network::VertexMap::iterator start, end, next;
//	start = tmp.getVertexMap().begin();
//
//


	//return true;
