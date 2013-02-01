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


class Network
{

	friend class ostream;

	public:
		Network();

		Network(Network* net);

		Network(const Network& net);

		Network(const ::std::vector< ::std::string>& nodes, const ::std::vector< ::std::pair< ::std::string, ::std::string> >& edges);

		virtual ~Network();

		/** Maximum degree per vertex. */
		::std::size_t degree;


	protected:


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

		typedef ::std::pair< ::std::string, ::std::string> EdgePair;

		typedef ::std::vector< EdgePair> EdgeVector;

		EdgeVector edges;


	public:

		Vertex findLeafNode();

		std::vector< Vertex> getLeafNodes();

		Vertex addVertex(const std::string& name, const std::vector< Vertex >& parents = std::vector< Vertex>());

		void removeVertex(const Vertex& v);

		void removeVertex(const ::std::string& vertexName);

		Edge addEdge(const Vertex& u, const Vertex& v, const std::string& property = "", const std::string& color = "black");

		Edge addEdge(const ::std::string& u, const ::std::string& v, const ::std::string& property = "", const ::std::string& color = "black");

		Edge addEdge(const Edge& e);

		Edge addEdge(const EdgePair& e);

		void removeEdge(const Edge& e);

		void removeEdge(const EdgePair& e);

		void removeEdge(const Vertex&u, const Vertex& v);

		void reverseEdge(const Edge& e);

		Vertex getVertex(const std::string& name);

		Edge getEdge(const std::string& source, const ::std::string& target);

		Edge getEdge(const Vertex& source, const Vertex& target);

		::std::size_t getNumEdges() const;

		::std::size_t getNumVertices() const;

//		Graph getGraph() const;

		void printGraph(std::ofstream& outf);

		const VertexMap& getVertexMap()  const {return this->vertexMap;};

		const EdgeVector& getEdgeVector()  const {return this->edges;};

		::std::size_t getDegree() const {return this->degree;};

		VertexBundle getVertexProperties(const ::std::string& vertexName);

		EdgeBundle getEdgeProperties(const Edge& e);

		void setEdgeProperties(const Edge& e, const EdgeBundle& props);

		void setVertexProperties(const Vertex& v, const VertexBundle& props);

		const VertexBundle& getVertexProperties(const ::std::string& vertexName) const;

		const EdgeBundle& getEdgeProperties(const Edge& e) const;

		std::vector< ::std::string> getParents(const Vertex& v);

		std::vector< ::std::string> getParents(const ::std::string& vertexName);

		bool operator == ( const Network& net);

		static bool isAcyclic(Network* graph);

		static void generateRandomNetwork(Network& net,
											  const ::std::vector< ::std::string>& nodes,
											  const ::std::vector< ::std::string>& nodeOrdering = ::std::vector< ::std::string>(),
											  const ::std::vector< EdgePair>& requiredEdges = ::std::vector< EdgePair>(),
											  const ::std::vector< EdgePair>& prohibitedEdges = ::std::vector< EdgePair>());

		static void randomizeNetwork(Network& net,
										const ::std::vector< ::std::string>& nodeOrdering = ::std::vector< ::std::string>(),
										const ::std::vector< EdgePair>& requiredEdges = ::std::vector< EdgePair>(),
										const ::std::vector< EdgePair>& prohibitedEdges = ::std::vector< EdgePair>());

		static bool isNetworkConsistent(const Network& net);

	protected:

		bool isAcyclic();


};

#endif /* NETWORK_H_ */
