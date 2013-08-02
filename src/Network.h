/*
 * Network.h
 *
 *  Created on: 21 Jan 2013
 *      Author: george
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include "NetworkDefs.h"

class Network
{

	friend class ostream;

	public:
		Network();

		Network(Network* net);

		Network(const Network& net);

		Network(const ::std::vector< ::std::string>& nodes,
				 const ::std::vector< ::std::pair< ::std::string, ::std::string> >& edges);


		//add network constructor when using edges and vertices
		//Network()

		virtual ~Network();

		/** Maximum degree per vertex. */
		::std::size_t degree;




	public:

		//Vertex Manipulation
		Vertex addVertex(const std::string& name, const std::vector< Vertex >& parents = std::vector< Vertex>());

		void removeVertex(const Vertex& v);

		void removeVertex(const ::std::string& vertexName);

		bool isVertex(const ::std::string& vertexName);

		Vertex getVertex(const std::string& name);

		//Edge Manipulation
		bool isEdge(const ::std::string& source, const ::std::string& target);

		Edge addEdge(const Vertex& u, const Vertex& v, const std::string& property = "", const std::string& color = "black");

		Edge addEdge(const ::std::string& u, const ::std::string& v, const ::std::string& property = "", const ::std::string& color = "black");

		Edge addEdge(const Edge& e);

		Edge addEdge(const EdgePair& e);

		void removeEdge(const Edge& e);

		void removeEdge(const EdgePair& e);

		void removeEdge(const Vertex&u, const Vertex& v);

		void reverseEdge(const Edge& e);

		Edge getEdge(const std::string& source, const ::std::string& target);

		Edge getEdge(const Vertex& source, const Vertex& target);

		//graph interface

		::std::size_t getNumEdges() const;

		::std::size_t getNumVertices() const;

		std::vector< Vertex> getLeafNodes();

		Graph& getGraph() {return this->graph;};

		void printGraph(std::ofstream& outf);

		VertexMap getVertexMap()  const {return this->vertexMap;};

		EdgeVector getEdgeVector()  const {return this->edges;};

		::std::vector < ::std::string> getVertexList();

		::std::size_t getDegree() const {return this->degree;};

		VertexBundle getVertexProperties(const ::std::string& vertexName);

		EdgeBundle getEdgeProperties(const Edge& e);

		void setEdgeProperties(const Edge& e, const EdgeBundle& props);

		void setVertexProperties(const Vertex& v, const VertexBundle& props);

		const VertexBundle& getVertexProperties(const ::std::string& vertexName) const;

		const EdgeBundle& getEdgeProperties(const Edge& e) const;

		std::vector< ::std::string> getParents(const Vertex& v);

		std::vector< ::std::string> getParents(const ::std::string& vertexName);

		void addRandomEdges( float probability);

		void removeRandomEdges( float probability);

		void setRequiredEdges( const EdgeVector& edges) { this->requiredEdges = edges;};

		void setProhibitedEdges( const EdgeVector& edges) { this->prohibitedEdges = edges;};

		void setNodeOrdering( const ::std::vector< ::std::string>& nodeOrdering) { this->nodeOrdering = nodeOrdering;};

		bool operator == ( const Network& net);

		void randomizeNetwork();

		bool isNetworkConsistent();

		bool isAcyclic();

		static Network  generateRandomNetwork(const ::std::vector< ::std::string>& nodes,
												  const ::std::vector< ::std::string>& nodeOrdering = ::std::vector< ::std::string>(),
											      const ::std::vector< EdgePair>& requiredEdges = ::std::vector< EdgePair>(),
											      const ::std::vector< EdgePair>& prohibitedEdges = ::std::vector< EdgePair>());

		Vertex findLeafNode();

	protected:



		void getPossibleParents(const ::std::string& node, const ::std::vector< ::std::string>& nodes,
								   const NodeOrdering& nodeOrdering,
								   ::std::vector< ::std::string>& parents);



	protected:

		Graph graph;

		VertexMap vertexMap;

		EdgeVector edges;

		NodeOrdering nodeOrdering;

		EdgeVector requiredEdges;

		EdgeVector prohibitedEdges;

};

#endif /* NETWORK_H_ */
