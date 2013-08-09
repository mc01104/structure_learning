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

//TODO:also replicate required, prohibited and node ordering in the copy constructors
//TODO:the degree - i.e. number of possible parents should be a parameter in construction
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

	//this->requiredEdges = net->getRequiredEdges();
	this->prohibitedEdges = net->getProhibitedEdges();
	this->nodeOrdering = net->getNodeOrdering();
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

	//this->requiredEdges = net.getRequiredEdges();
	this->prohibitedEdges = net.getProhibitedEdges();
	this->nodeOrdering = net.getNodeOrdering();

}


Network::Network(const ::std::vector< ::std::string>& nodes, const ::std::vector< ::std::pair< ::std::string, ::std::string> >& edges):
		degree(10)
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


//const VertexBundle&
//Network::getVertexProperties(const ::std::string& vertexName) const
//{
//	return this->graph[this->vertexMap[vertexName]];
//}
//
//const EdgeBundle&
//Network::getEdgeProperties(const Edge& e) const
//{
//	return this->graph[e];
//}

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


Network*
Network::generateRandomNetwork(const ::std::vector< ::std::string>& nodes,
								   const ::std::vector< ::std::string>& nodeOrdering,
								   const ::std::vector< EdgePair>& requiredEdges,
								   const ::std::vector< EdgePair>& prohibitedEdges)
{
	//generate random network
	Network* tmp = new Network(nodes,requiredEdges);

	tmp->setNodeOrdering(nodeOrdering);
	tmp->setProhibitedEdges(prohibitedEdges);

	return tmp->randomizeNetwork();
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
Network::addRandomEdge(float probability)
{

	if(rand.randFloat(0.0,1.0) > probability) return;

	int node_ind = rand.randInt(0,this->getNumVertices() - 1);

	::std::string node_name = this->getVertexList()[node_ind];

	Vertex v = this->getVertex(node_name);

	int vertex_degree = this->getDegree() - this->getGraph()[v].parents.size();

	if (vertex_degree == 0) return;

	::std::vector< ::std::string> parents;
	 this->getPossibleParents(node_name,this->getVertexList(),this->nodeOrdering,parents);

	 int parent_ind = rand.randInt(0, parents.size() - 1);

	 EdgePair edge(parents[parent_ind], node_name);

	 if(this->isEdgeProhibited(edge)) return;

	 if( !this->isEdge(parents[parent_ind], node_name) && !this->isEdge(node_name,parents[parent_ind]))
	 	 this->addEdge(parents[parent_ind], node_name);

	 if(!this->isAcyclic())
		 this->removeEdge(EdgePair(parents[parent_ind], node_name));


}

void
Network::removeRandomEdge(float probability)
{
	int edge_ind = rand.randInt(0,this->getEdgeVector().size() - 1);

	EdgePair edge = this->getEdgeVector()[edge_ind];

	if (this->isEdgeRequired(edge)) return;

	if(rand.randFloat(0.0,1.0) > probability) return;

	this->removeEdge(edge);
}

//TODO probabilities of adding and removing edges shouldn't be handcoded
Network*
Network::randomizeNetwork()
{
	Network* tmp = new Network(this);

	for(int i = 0; i < 100; i++)
		tmp->addRandomEdge(0.2);

	for(int i = 0; i < 10; i++)
		if (tmp->getNumEdges() > 0)
			tmp->removeRandomEdge(0.2);

	return tmp;
}


bool
Network::isEdgeRequired(const EdgePair& edge)
{
	if(::std::find(this->requiredEdges.begin(), this->requiredEdges.end(), edge) == requiredEdges.end())
		return false;

	return true;
}

bool
Network::isEdgeProhibited(const EdgePair& edge)
{
	if(::std::find(this->prohibitedEdges.begin(), this->prohibitedEdges.end(), edge) == prohibitedEdges.end())
		return false;

	return true;
}

bool
Network::checkForRequiredEdges()
{
	for(EdgeVector::iterator it = this->requiredEdges.begin(); it != this->requiredEdges.end(); ++it)
		if(::std::find(this->edges.begin(), this->edges.end(), *it) == this->edges.end())
			return false;

	return true;
}

bool
Network::checkForProhibitedEdges()
{
	for(EdgeVector::iterator it = prohibitedEdges.begin(); it != prohibitedEdges.end(); ++it)
		if(::std::find(this->edges.begin(), this->edges.end(), *it) == this->edges.end())
			return false;

	return true;
}

void
Network::getPossibleParents(const ::std::string& node, const ::std::vector< ::std::string>& nodes,
							    const NodeOrdering& nodeOrdering,
							    ::std::vector< ::std::string>& parents)
{
	::std::vector< ::std::string> prohibitedParents;

	NodeOrdering::const_iterator index = ::std::find(nodeOrdering.begin(), nodeOrdering.end(), node);

	if (index != nodeOrdering.end())
	{
		NodeOrdering::const_iterator it;
		for(it = index; it != nodeOrdering.end(); ++it)
			prohibitedParents.push_back(*it);
	}
	else
	{
		prohibitedParents.push_back(node);
	}

	parents = const_cast< ::std::vector< ::std::string>& >(nodes) - prohibitedParents;

}

bool
Network::isVertex(const ::std::string& vertexName)
{
	for(VertexMap::iterator it = this->vertexMap.begin(); it != this->vertexMap.end(); ++it)
		if(it->first == vertexName)
			return true;

	return false;

}

bool
Network::isEdge(const ::std::string& source, const ::std::string& target)
{
	EdgePair edge(source,target);

	if (::std::find(this->edges.begin(),this->edges.end(),edge) != this->edges.end())
		return true;

	return false;
}

bool
Network::isNetworkConsistent()
{
	return this->checkForRequiredEdges() || this->checkForProhibitedEdges() || this->isAcyclic();
}
