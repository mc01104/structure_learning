/*
 * Network.cpp
 *
 *  Created on: 21 Jan 2013
 *      Author: george
 */

#include <boost/graph/graphviz.hpp>
#include <algorithm>

#include "Utilities.h"
#include "Network.h"

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
		this->addEdge(*iter);

}

Network::~Network()
{

}

Vertex
Network::addVertex(const std::string& name, const std::vector< Vertex>& parents)
{
	Vertex v = ::boost::add_vertex(this->graph);

	this->graph[v].id = ::boost::num_vertices(this->graph) - 1;

	this->graph[v].rank = this->degree;

	this->graph[v].name = name;

	this->vertexMap[name] = v;

	return v;
}

Edge
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

Edge
Network::addEdge(const ::std::string& u, const ::std::string& v, const ::std::string& property, const ::std::string& color)
{
	Vertex v1 = this->vertexMap[u];

	Vertex v2 = this->vertexMap[v];

	return this->addEdge(v1,v2,property,color);

}

Edge
Network::addEdge(const Edge& e)
{
	Vertex v1 = ::boost::source(e, this->graph);

	Vertex v2 = ::boost::target(e, this->graph);

	::std::string property = this->graph[e].property;

	::std::string color = this->graph[e].color;

	return this->addEdge(v1,v2,property,color);
}

Edge
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
	Network* tmp = new Network(this);

	size_t numOfVertices = tmp->getNumVertices();

	if( numOfVertices == 0)
	{
		return true;
	}

	if ( tmp->getLeafNodes().size() == 0)
		return false;

	Vertex v;

	v = tmp->findLeafNode();

	if(v)
	{
		tmp->removeVertex(v);
		return tmp->isAcyclic();
	}

	delete tmp;
	return false;

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


	std::vector<Vertex>::iterator start = this->graph[::boost::target(e, this->graph)].parents.begin();

	std::vector<Vertex>::iterator end = this->graph[::boost::target(e, this->graph)].parents.end();

	for(std::vector<Vertex>::iterator it = start; it != end; it++)
	{
		if(*it == ::boost::source(e, this->graph))
		{
			this->graph[::boost::target(e, this->graph)].parents.erase(it);
		}
	}
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

Vertex
Network::getVertex(const std::string& name)
{
	return vertexMap[name];
}

Edge
Network::getEdge(const Vertex& source, const Vertex& target)
{
	return ::boost::edge(source, target, this->getGraph()).first;

}

Edge
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

Vertex
Network::findLeafNode()
{
	VertexMap::iterator it;

	for(it = this->vertexMap.begin(); it != this->vertexMap.end(); ++it)
		if(::boost::out_degree(it->second, this->getGraph()) == 0 )
			return it->second;

	return NULL;
}


std::vector< Vertex>
Network::getLeafNodes()
{
	std::map< std::string, Vertex>::iterator it;

	std::vector< Vertex> leafNodes;

	for(it = this->vertexMap.begin(); it != this->vertexMap.end(); ++it)
		if( ::boost::out_degree(it->second, this->graph) == 0)
			leafNodes.push_back(it->second);

	return leafNodes;
}


VertexBundle
Network::getVertexProperties(const ::std::string& vertexName)
{
	return this->graph[this->vertexMap[vertexName]];
}

EdgeBundle
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

const VertexBundle&
Network::getVertexProperties(const ::std::string& vertexName) const
{
	return this->graph[this->vertexMap.at(vertexName)];
}

const EdgeBundle&
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


Network
Network::generateRandomNetwork(const ::std::vector< ::std::string>& nodes,
								   const ::std::vector< ::std::string>& nodeOrdering,
								   const ::std::vector< EdgePair>& requiredEdges,
								   const ::std::vector< EdgePair>& prohibitedEdges)
{
	//generate random network
	Network* tmp = new Network(nodes,requiredEdges);

	tmp->setNodeOrdering(nodeOrdering);

	tmp->setRequiredEdges(requiredEdges);

	tmp->setProhibitedEdges(prohibitedEdges);

	tmp->addRandomEdges(0.5);

	//remove prohibited edges
	for( ::std::vector< EdgePair>::const_iterator it = prohibitedEdges.begin(); it != prohibitedEdges.end(); ++it)
		if(tmp->isEdge(it->first, it->second))
			tmp->removeEdge(*it);

	//check if graph is acyclic
	if (tmp->isAcyclic())
		return *tmp;

	delete tmp;

	return Network::generateRandomNetwork(nodes, nodeOrdering, requiredEdges, prohibitedEdges);
}

::std::vector < ::std::string>
Network::getVertexList()
{
	::std::vector< ::std::string> vertexList;

	for( VertexMap::iterator it = this->vertexMap.begin(); it != this->vertexMap.end(); ++it)
		vertexList.push_back(it->first);

	return vertexList;
}

void
Network::addRandomEdges(float probability)
{
	for( VertexMap::const_iterator it = this->vertexMap.begin(); it != this->vertexMap.end(); ++it)
	{
		::std::vector< ::std::string> parents;

		this->getPossibleParents(it->first, this->getVertexList(), this->nodeOrdering, parents);

		//generate edge with probability 50%
		int edgeCounter = this->getDegree() - this->getParents(this->getVertex(it->first)).size();

		for (int i =0; i < edgeCounter; ++i)
		{
			if( generateRandomFloat(0.0,1.0) <= probability)
			{
				int index = generateRandomInt(0,parents.size() - 1);

				if( !this->isEdge(it->first, parents[index]))
					this->addEdge(it->first,parents[index]);
			}
		}
	}
}

void
Network::removeRandomEdges(float probability)
{
	for( EdgeVector::iterator it = this->edges.begin(); it != this->edges.end(); ++it)
		if( generateRandomFloat(0,1) <= probability)
			this->removeEdge(*it);

}

void
Network::randomizeNetwork()
{
	//remove random edges
	this->removeRandomEdges(0.4);

	//add random edges
	this->addRandomEdges(0.1);

	while(!this->isAcyclic())
		this->randomizeNetwork();

}


void
Network::getPossibleParents(const ::std::string& node, const ::std::vector< ::std::string>& nodes,
							    const NodeOrdering& nodeOrdering,
							    ::std::vector< ::std::string>& parents)
{
	::std::vector< ::std::string> prohibitedParents;

	NodeOrdering::const_iterator index = ::std::find(nodeOrdering.begin(), nodeOrdering.end(), node);

	if(index != nodeOrdering.end())
		::std::copy(index, nodeOrdering.end(), prohibitedParents.begin());

	parents = const_cast< ::std::vector< ::std::string>& >(nodes) - prohibitedParents;
}

bool
Network::isVertex(const ::std::string& vertexName)
{
	for(VertexMap::iterator it = this->vertexMap.begin(); it != this->vertexMap.end(); ++it)
	{
		if(it->first == vertexName)
			return true;
	}

	return false;

}

bool
Network::isEdge(const ::std::string& source, const ::std::string& target)
{
	for(EdgeVector::iterator it = this->edges.begin(); it != this->edges.end(); ++it)
	{
		if(it->first == source && it->second == target)
			return true;
	}

	return false;
}

bool
Network::isNetworkConsistent()
{
	if (!this-isAcyclic()) return false;

	//check for required edges

	//check for prohibited edges

	//check node ordering

	return true;
}
