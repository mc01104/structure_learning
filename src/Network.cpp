/*
 * Network.cpp
 *
 *  Created on: 21 Jan 2013
 *      Author: george
 */
#include <boost/graph/graphviz.hpp>
#include <algorithm>

#include "Network.h"
#include "Verifier.h"


Network::Network():
degree(10),
graph()
{
}

Network::Network(Network* net)
{
	this->degree = net->getDegree();

	VertexMap tmp = net->getVertexMap();

	VertexMap::iterator it;

	for( it = tmp.begin(); it != tmp.end(); ++it )
		this->addVertex(it->first);

	EdgeVector tmpEdges = net->getEdgeVector();

	EdgeVector::iterator iter;

	for( iter = tmpEdges.begin(); iter != tmpEdges.end(); ++iter)
		this->addEdge(this->vertexMap[iter->first],this->vertexMap[iter->second]);
}

Network::Network(const Network& net)
{
	this->degree = net.getDegree();

	VertexMap tmp = net.getVertexMap();

	VertexMap::const_iterator it;

	for( it = tmp.begin(); it != tmp.end(); ++it )
		this->addVertex(it->first);

	EdgeVector tmpEdges = net.getEdgeVector();

	EdgeVector::const_iterator iter;

	for( iter = tmpEdges.begin(); iter != tmpEdges.end(); ++iter)
		this->addEdge(this->vertexMap[iter->first],this->vertexMap[iter->second]);
}

Network::Network(const ::std::vector< ::std::string>& nodes, const ::std::vector< ::std::pair< ::std::string, ::std::string> >& edges)
{
	::std::vector< ::std::string>::const_iterator it;

	::std::vector< ::std::pair< ::std::string, ::std::string> >::const_iterator iter;

	for(it = nodes.begin(); it != nodes.end(); ++it)
		this->addVertex(*it);

	for(iter = edges.begin(); iter != edges.end(); ++iter)
		this->addEdge(iter->first,iter->second);

}

Network::~Network()
{

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

	::std::string source = this->graph[u].name;

	::std::string target = this->graph[v].name;

	edges.push_back(EdgePair(source,target));

	return e;
}

Network::Edge
Network::addEdge(const ::std::string& u, const ::std::string& v, const ::std::string& property, const ::std::string& color)
{
	Vertex v1 = this->vertexMap[u];

	Vertex v2 = this->vertexMap[v];

	return this->addEdge(v1,v2,property,color);

}

Network::Edge
Network::addEdge(const Edge& e)
{
	Vertex v1 = ::boost::source(e, this->graph);

	Vertex v2 = ::boost::target(e, this->graph);

	::std::string property = this->graph[e].property;

	::std::string color = this->graph[e].color;

	return this->addEdge(v1,v2,property,color);
}

Network::Edge
Network::addEdge(const EdgePair& e)
{
	Vertex v1 = this->vertexMap[e.first];

	Vertex v2 = this->vertexMap[e.second];

	return this->addEdge(v1,v2);
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


bool
Network::isAcyclic()
{
	size_t numOfVertices = this->getNumVertices();

	if( numOfVertices == 0)
	{
		return true;
	}

	if ( this->getLeafNodes().size() == 0)
		return false;

	Network::Vertex v;

	v = this->findLeafNode();

	if(v)
	{
		this->removeVertex(v);
		return this->isAcyclic();
	}

	return false;

}

bool
Network::isAcyclic(Network* graph)
{
	Network tmp(graph);

	return tmp.isAcyclic();
}


void
Network::removeEdge(const Edge& e)
{

	VertexBundle source, target;

	source = this->graph[::boost::source(e, this->graph)];

	target = this->graph[::boost::target(e, this->graph)];


	EdgePair edge(source.name,target.name);

	for( EdgeVector::iterator it = this->edges.begin(); it != this->edges.end(); ++it)
		if(*it == edge)
		{
			this->edges.erase(it);
			break;
		}


	std::vector<Vertex>::iterator start = target.parents.begin();

	std::vector<Vertex>::iterator end = target.parents.end();

	for(std::vector<Vertex>::iterator it = start; it != end; ++it)
		if(*it == ::boost::source(e, this->graph))
			target.parents.erase(it);

	::boost::remove_edge(e, this->graph);
}

void
Network::removeEdge(const Vertex&u, const Vertex& v)
{
	Edge tmp = this->getEdge(u,v);
	this->removeEdge(tmp);
}


void
Network::removeEdge(const EdgePair& e)
{
	Vertex source = this->vertexMap[e.first];

	Vertex target = this->vertexMap[e.second];

	Edge tmp = this->getEdge(source,target);

	this->removeEdge(tmp);

}


void
Network::removeVertex(const Vertex& v)
{
	std::string name = this->graph[v].name;

	std::vector< Vertex> parents = this->graph[v].parents;

	for(std::vector< Vertex>::iterator it = parents.begin(); it != parents.end(); ++it )
		this->removeEdge(*it,v);
		//::boost::remove_edge(*it,v,this->graph);

	::boost::remove_vertex(v, this->graph);

	this->vertexMap.erase(name);

}

void
Network::removeVertex(const ::std::string& vertexName)
{
	this->removeVertex(this->vertexMap[vertexName]);
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

Network::Edge
Network::getEdge(const ::std::string& source, const ::std::string& target)
{
	Vertex v1 = this->vertexMap[source];

	Vertex v2 = this->vertexMap[target];

	return this->getEdge(v1,v2);

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
	VertexMap::iterator it;

	for(it = this->vertexMap.begin(); it != this->vertexMap.end(); ++it)
		if(::boost::out_degree(it->second, this->graph) == 0)
			return it->second;

	return NULL;
}


std::vector< Network::Vertex>
Network::getLeafNodes()
{
	std::map< std::string, Vertex>::iterator it;

	std::vector< Vertex> leafNodes;

	for(it = this->vertexMap.begin(); it != this->vertexMap.end(); ++it)
		if( ::boost::out_degree(it->second, this->graph) == 0)
			leafNodes.push_back(it->second);

	return leafNodes;
}


Network::VertexBundle
Network::getVertexProperties(const ::std::string& vertexName)
{
	return this->graph[this->vertexMap[vertexName]];
}

Network::EdgeBundle
Network::getEdgeProperties(const Edge& e)
{
	return this->graph[e];
}

void
Network::setEdgeProperties(const Edge& e, const EdgeBundle& props)
{
	this->graph[e] = props;
}

void
Network::setVertexProperties(const Vertex& v, const VertexBundle& props)
{
	this->graph[v] = props;
}

const Network::VertexBundle&
Network::getVertexProperties(const ::std::string& vertexName) const
{
	return this->graph[this->vertexMap.at(vertexName)];
}

const Network::EdgeBundle&
Network::getEdgeProperties(const Edge& e) const
{
	return this->graph[e];
}

::std::vector< ::std::string>
Network::getParents(const Vertex& v)
{
	::std::vector< ::std::string> parents;

	::std::vector< Vertex>::iterator it;

	for(it = this->graph[v].parents.begin(); it != this->graph[v].parents.end(); ++it)
		parents.push_back(this->graph[*it].name);

	return parents;
}

std::vector< ::std::string>
Network::getParents(const ::std::string& vertexName)
{
	Vertex v = this->vertexMap[vertexName];

	return this->getParents(v);
}



bool
Network::operator==(const Network& net)
{
	VertexMap::const_iterator vertexIter;

	EdgeVector::const_iterator edgeIter;

	if( this->getNumVertices() != net.getNumVertices())
		return false;

	if( this->getNumEdges() != net.getNumEdges())
		return false;

	for(vertexIter = this->getVertexMap().begin(); vertexIter != this->getVertexMap().end(); ++vertexIter)
		if(!net.getVertexMap().at(vertexIter->first))
			return false;

	for(edgeIter = this->getEdgeVector().begin(); edgeIter != this->getEdgeVector().end(); ++edgeIter)
		if(::std::find(net.getEdgeVector().begin(), net.getEdgeVector().end(), *edgeIter) == net.getEdgeVector().end())
			return false;


	return true;
}





