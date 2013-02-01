//============================================================================
// Name        : test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "stdlib.h"
#include "stdio.h"
#include <tinyxml.h>
#include <vector>
#include "ProblemFactory.h"
#include "Problem.h"
#include "Network.h"

using namespace std;
bool isAcyclic(Network* graph);
int main(int argc, char* argv[]) {

//	if (argc < 2)
//		cerr << " Please specify the path to the settings file for this experiment" << endl;
//
//	sl::ProblemFactory* pFactory = sl::ProblemFactory::getInstance();
//
//	sl::Problem* problem = pFactory->create(argv[1]);
//
//	cout << *problem << endl;
//
//	pFactory->destroy(problem);

	Network* g = new Network();

	g->addVertex("George");
	g->addVertex("Spyros");
	g->addVertex("Mpampis");

	cout <<"Number of vertices should be 3 ?=" << g->getNumVertices() << endl;

	//List Vertices
	std::cout << "List of nodes" << std::endl;

	std::map< std::string, void*>::const_iterator it = g->getVertexMap().begin();

	for(int i = 0; i < static_cast<int>(g->getNumVertices()); ++i)
	{
		std::cout << ( it++)->first << std::endl;
	}

	//same thing with iterators
	std::cout << "same thing with iterators " << std::endl;


	Network::VertexMap::const_iterator it2;

	for(it2 = g->getVertexMap().begin(); it2 != g->getVertexMap().end(); ++it2)
		std::cout << it2->first << std::endl;

	//Add an edge
	Network::Edge e1 = g->addEdge(g->getVertex("George"),g->getVertex("Spyros"));

	std::cout << "An edge was created" << std::endl;
//
//	std::cout << "Number of edges: " << g->getNumEdges() << std::endl;
//
//	//void* nsource = ::boost::source(e1,g->getGraph());
//
//	//void* ntarget = ::boost::target(e1,g->getGraph());
//
//	//std::cout << "parent =" << g->getGraph()[nsource].name << ", child = " << g->getGraph()[ntarget].name << std::endl;
//
//	//std::cout << g->getGraph()[g->getVertexMap()[g->getGraph()[nsource].name]].name << " is the parent" << std::endl;
//
//	if(g->getGraph()[ntarget].parents.front() == nsource)
//		std::cout << "parents updated correctly" << std::endl;
//
//	g->removeVertex(g->getVertex("Spyros"));
//
//	std::cout << "Number of edges: " << g->getNumEdges() << std::endl;
//
//	//List Vertices
//	std::cout << "List of nodes" << std::endl;
//
//	it = g->getVertexMap().begin();
//
//	for(int i = 0; i < static_cast<int>(g->getNumVertices()); ++i)
//		std::cout << ( it++)->first << std::endl;
//
//	g->addVertex("Spyros");
//
//	std::cout << "Mpampis has " << g->getGraph()[g->getVertex("Mpampis")].parents.size() << " parents" << std::endl;
//
//	e1 = g->addEdge(g->getVertex("George"),g->getVertex("Mpampis"));
//
//	std::cout << "An edge was created" << std::endl;
//
//	std::cout << "Number of edges: " << g->getNumEdges() << std::endl;
//
//	std::cout << "Mpampis has " << g->getGraph()[g->getVertex("Mpampis")].parents.size() << " parents" << std::endl;
//
//	nsource = ::boost::source(e1,g->getGraph());
//
//	ntarget = ::boost::target(e1,g->getGraph());
//
//	std::cout << "parent =" << g->getGraph()[nsource].name << ", child = " << g->getGraph()[ntarget].name << std::endl;
//
//	//std::cout << g->getGraph()[g->getVertexMap()[g->getGraph()[nsource].name]].name << " is the parent" << std::endl;
//
//	if(g->getGraph()[ntarget].parents.front() == nsource)
//		std::cout << "parents updated correctly" << std::endl;
//
//	g->removeEdge(e1);
//
//	std::cout << "Number of edges: " << g->getNumEdges() << std::endl;
//
//	std::cout << "Mpampis has " << g->getGraph()[g->getVertex("Mpampis")].parents.size() << " parents" << std::endl;
//
//	if(g->getGraph()[g->getVertex("Mpampis")].parents.front() == NULL)
//		std::cout << "parents NOT updated correctly" << std::endl;
//
//

	g->addEdge(g->getVertex("George"),g->getVertex("Mpampis"));

	g->addEdge(g->getVertex("Mpampis"),g->getVertex("Spyros"));

	//Network::Edge e4 = g->addEdge(g->getVertex("Spyros"),g->getVertex("George"));

	std::cout << "These are the leafnodes of the graph" << endl;

	std::vector< Network::Vertex> leafnodes = g->getLeafNodes();

//	if(leafnodes.size() > 0)
//		for(std::vector< Network::Vertex>::iterator it = leafnodes.begin(); it != leafnodes.end(); ++it)
//			cout << g->getGraph()[*it].name << endl;


	Network::Vertex v = g->findLeafNode();

//	if(v)
//		std::cout <<"Node name :" <<  g->getGraph()[v].name << std::endl;


	Network tmp(g);
	cout << tmp.getNumEdges() << endl;
	cout << tmp.getNumVertices() << endl;
	cout << tmp.getLeafNodes().size() << endl;

	if (Network::isAcyclic(g))
		cout << "graph is acyclic" << endl;
	else
		cout << "graph is cyclic" << endl;

	cout << g->getNumVertices() << endl;

    return 0;
}
