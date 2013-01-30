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
	std::map< std::string, void*>::iterator it = g->getVertexMap().begin();
	for(int i = 0; i < static_cast<int>(g->getNumVertices()); ++i)
	{
		std::cout << ( it++)->first << std::endl;
	}

	Network::Edge e1 = g->addEdge(g->getVertex("George"),g->getVertex("Spyros"));

	std::cout << "An edge was created" << std::endl;
	std::cout << "Number of edges: " << g->getNumEdges() << std::endl;
	void* nsource = ::boost::source(e1,g->getGraph());
	void* ntarget = ::boost::target(e1,g->getGraph());
	std::cout << "parent =" << g->getGraph()[nsource].name << ", child = " << g->getGraph()[ntarget].name << std::endl;
	std::cout << g->getGraph()[g->getVertexMap()[g->getGraph()[nsource].name]].name << " is the parent" << std::endl;
	if(g->getGraph()[ntarget].parents.front() == nsource)
		std::cout << "parents updated correctly" << std::endl;

	g->removeVertex(g->getVertex("Spyros"));

	std::cout << "Number of edges: " << g->getNumEdges() << std::endl;
	//List Vertices
	std::cout << "List of nodes" << std::endl;
	it = g->getVertexMap().begin();
	for(int i = 0; i < static_cast<int>(g->getNumVertices()); ++i)
	{
		std::cout << ( it++)->first << std::endl;
	}

	g->addVertex("Spyros");


	std::cout << "Mpampis has " << g->getGraph()[g->getVertex("Mpampis")].parents.size() << " parents" << std::endl;

	e1 = g->addEdge(g->getVertex("George"),g->getVertex("Mpampis"));


	std::cout << "An edge was created" << std::endl;
	std::cout << "Number of edges: " << g->getNumEdges() << std::endl;
	std::cout << "Mpampis has " << g->getGraph()[g->getVertex("Mpampis")].parents.size() << " parents" << std::endl;
	nsource = ::boost::source(e1,g->getGraph());
	ntarget = ::boost::target(e1,g->getGraph());
	std::cout << "parent =" << g->getGraph()[nsource].name << ", child = " << g->getGraph()[ntarget].name << std::endl;
	std::cout << g->getGraph()[g->getVertexMap()[g->getGraph()[nsource].name]].name << " is the parent" << std::endl;
	if(g->getGraph()[ntarget].parents.front() == nsource)
		std::cout << "parents updated correctly" << std::endl;

	g->removeEdge(e1);

	std::cout << "Number of edges: " << g->getNumEdges() << std::endl;
	std::cout << "Mpampis has " << g->getGraph()[g->getVertex("Mpampis")].parents.size() << " parents" << std::endl;

	if(g->getGraph()[g->getVertex("Mpampis")].parents.front() == NULL)
		std::cout << "parents NOT updated correctly" << std::endl;

	//	cout << g->getNumVertices() << endl;
//
	//g->addEdge(g->getVertex("George"),g->getVertex("Mpampis"));
//
//	cout << g->getNumEdges() << endl;
//
//	g->removeEdge(g->getEdge(g->getVertex("George"), g->getVertex("Mpampis")));
//
	//g->addEdge(g->getVertex("Mpampis"),g->getVertex("Spyros"));


//	g->addEdge(g->getVertex("Spyros"),g->getVertex("George"));

//	g->reverseEdge(g->getEdge(g->getVertex("George"), g->getVertex("Mpampis")));
//
//	cout << g->getNumEdges() << endl;
//
//	std::ofstream outf("test2.dot");
//	g->printGraph(outf);
//	outf.close();
//
//	//test:	void randomize();
//
//	g->removeVertex(g->getVertex("George"));
//	g->addVertex("Giannis");
//	g->addVertex("Mitsos");
//	cout << "num:" <<g->getNumVertices() << endl;
	if(isAcyclic(g))
	{
		cout << "the graph is acyclic" << endl;
	}

    return 0;
}

bool isAcyclic(Network* graph)
{
	size_t numOfVertices = graph->getNumVertices();

	if( numOfVertices == 0)
	{
		return true;
	}

	Network::Vertex v;

	std::cout << "find a leaf node" << std::endl;
	v = graph->findLeafNode();
	std::cout << "leaf node found" << std::endl;
	//cout << graph->getGraph()[*graph->getGraph()[v].parents.begin()].name << endl;
	if(v)
		std::cout <<"Node name :" <<  graph->getGraph()[v].name << std::endl;

	if(v)
	{
		std::cout << "Remove the leaf node" << std::endl;
		graph->removeVertex(graph->get);
		std::cout << "Leaf Node Removed" << std::endl;
		return isAcyclic(graph);
	}

	return false;

}
