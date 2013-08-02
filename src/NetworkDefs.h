/*
 * NetworkDefs.h
 *
 *  Created on: 1 Aug 2013
 *      Author: george
 */

#ifndef NETWORKDEFS_H_
#define NETWORKDEFS_H_

#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <map>

struct EdgeBundle
{
	int id;
	std::string property;
	std::string color;
};

typedef boost::adjacency_list_traits< boost::listS, boost::listS,
											   boost::directedS, boost::listS >::vertex_descriptor Vertex;

struct VertexBundle
{
	int id;
	int rank;
	std::string name;
	std::vector< Vertex > parents;
};

typedef boost::adjacency_list< boost::listS, boost::listS, boost::directedS, VertexBundle, EdgeBundle, boost::no_property> Graph;

typedef boost::graph_traits< Graph>::edge_descriptor Edge;

typedef boost::graph_traits< Graph>::vertex_iterator VertexIter;

typedef std::pair< VertexIter, VertexIter> VertexIterPair;

typedef ::std::map< ::std::string, Vertex > VertexMap;

typedef ::std::pair< ::std::string, ::std::string> EdgePair;

typedef ::std::vector< EdgePair> EdgeVector;

typedef ::std::vector< ::std::string> NodeOrdering;

#endif /* NETWORKDEFS_H_ */
