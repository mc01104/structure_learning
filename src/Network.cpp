/*
 * Network.cpp
 *
 *  Created on: 21 Jan 2013
 *      Author: george
 */
#include <boost/graph/graphviz.hpp>

#include "Network.h"
#include "Verifier.h"


Network::Network():
degree(10),
graph()
{
	this->verifier = new Verifier();
}

Network::~Network()
{
	delete verifier;
}

Network::Vertex
Network::addVertex(const std::string& name, const std::vector< Vertex>& parents)
{
	Vertex v = ::boost::add_vertex(this->graph);

	this->graph[v].id = ::boost::num_vertices(this->graph) - 1;

	this->graph[v].rank = this->degree;

	this->graph[v].name = name;

	this->vertexMap[name] = v;

	return v;
}

Network::Edge
Network::addEdge(const Vertex& u, const Vertex& v, const std::string& property, const std::string& color)
{
	Edge e = ::boost::add_edge(u,v,this->graph).first;

	this->graph[e].color = color;

	this->graph[e].id = ::boost::num_edges(this->graph) - 1;

	this->graph[e].property = property;

	this->graph[v].parents.push_back(u);

	return e;
}

::std::size_t
Network::getNumEdges() const
{
	return ::boost::num_edges(this->graph);
}

::std::size_t
Network::getNumVertices() const
{
	return ::boost::num_vertices(this->graph);
}

void
Network::randomize()
{

}

bool
Network::isAcyclic(Network& graph)
{
	return this->verifier->isAcyclic(*this);

}

Network::Graph
Network::getGraph() const
{
	//Graph g = this->graph;
	return this->graph;
}

void
Network::removeEdge(const Edge& e)
{

	std::vector<Vertex>::iterator start = this->getGraph()[::boost::target(e, this->graph)].parents.begin();

	std::vector<Vertex>::iterator end = this->getGraph()[::boost::target(e, this->graph)].parents.end();

	for(std::vector<Vertex>::iterator it = start; it != end; ++it)
		if(*it == ::boost::source(e, this->graph))
			this->getGraph()[::boost::target(e, this->graph)].parents.erase(it);

	::boost::remove_edge(e, this->graph);
}

void
Network::removeVertex(const Vertex& v)
{
	std::string name = this->graph[v].name;
std::cout << "1 " << std::endl;
	std::vector< Vertex> parents = this->graph[v].parents;
std::cout << "2 " << std::endl;
	for(std::vector< Vertex>::iterator it = parents.begin(); it != parents.end(); ++it )
	{
		std::cout << "3 " << std::endl;
		::boost::remove_edge(*it,v,this->graph);
		std::cout << "4 " << std::endl;
	}
	std::cout << "5 " << std::endl;
	std::cout << v << "  "  << std::endl;
	::boost::remove_vertex(v, this->graph);
	std::cout << "6 " << std::endl;
	this->vertexMap.erase(name);
	std::cout << "7 " << std::endl;
}

void
Network::reverseEdge(const Edge& e)
{
	Vertex n1 = ::boost::source(e, this->graph);

	Vertex n2 = ::boost::target(e, this->graph);

	std::string property = this->graph[e].property;

	std::string color = this->graph[e].color;

	this->removeEdge(e);

	this->addEdge(n2,n1,property,color);
}

Network::Vertex
Network::getVertex(const std::string& name)
{
	return vertexMap[name];
}

Network::Edge
Network::getEdge(const Vertex& source, const Vertex& target)
{
	return ::boost::edge(source, target, this->graph).first;
}

void
Network::printGraph(std::ofstream& outf)
{
	::boost::dynamic_properties dp;

	dp.property("label", boost::get(&VertexBundle::name, this->graph));

	dp.property("node_id", get(&VertexBundle::id, this->graph));

	boost::write_graphviz_dp(outf, this->graph, dp);

}

Network::Vertex
Network::findLeafNode()
{
	Network::VertexMap::iterator start = this->getVertexMap().begin();
	Network::VertexMap::iterator next;
//	for(next = start; next != this->getVertexMap().end(); ++next)
//	{
//		::std::cout << this->getGraph()[next->second].name << std::endl;
//	}


	for(int i = 0; i < this->getNumVertices(); ++i)
	{
		::boost::graph_traits< Graph>::degree_size_type type= ::boost::out_degree(start->second, this->getGraph());
		if(type == 0)
			return start->second;

		++start;
	}
	::std::cout << " big bug" << std::endl;
	return NULL;
}








