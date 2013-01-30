/*
 * Network.h
 *
 *  Created on: 21 Jan 2013
 *      Author: george
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <map>

class Verifier;

class Network
{
	friend class Verifier;

	friend class ostream;

	public:
		Network();

		virtual ~Network();

		/** Maximum degree per vertex. */
		::std::size_t degree;


	protected:
		Verifier* verifier;

		struct EdgeBundle
		{
			int id;
			std::string property;
			std::string color;
		};

	public:
		typedef boost::adjacency_list_traits< boost::listS, boost::listS,
											   boost::directedS, boost::listS >::vertex_descriptor Vertex;


		struct VertexBundle
		{
			int id;
			int rank;
			std::string name;
			std::vector< Vertex > parents;
		};

	public:
		typedef boost::adjacency_list< boost::listS, boost::listS, boost::directedS, VertexBundle, EdgeBundle, boost::no_property> Graph;


		typedef boost::graph_traits< Graph>::edge_descriptor Edge;

		typedef boost::graph_traits< Graph>::vertex_iterator VertexIter;

		typedef std::pair< VertexIter, VertexIter> VertexIterPair;

		Graph graph;

		typedef ::std::map< ::std::string, Vertex > VertexMap;

		VertexMap vertexMap;


	public:

		Vertex findLeafNode();

		Vertex addVertex(const std::string& name, const std::vector< Vertex >& parents = std::vector< Vertex>());

		void removeVertex(const Vertex& v);

		Edge addEdge(const Vertex& u, const Vertex& v, const std::string& property = "", const std::string& color = "black");

		void removeEdge(const Edge& e);

		void reverseEdge(const Edge& e);

		Vertex getVertex(const std::string& name);

		Edge getEdge(const Vertex& source, const Vertex& target);

		::std::size_t getNumEdges() const;

		::std::size_t getNumVertices() const;

		Graph getGraph() const;

		void randomize();

		bool isAcyclic(Network& graph);

		void printGraph(std::ofstream& outf);

		VertexMap getVertexMap() {return this->vertexMap;};

};

#endif /* NETWORK_H_ */
