/*
 * Network.h
 *
 *  Created on: 21 Jan 2013
 *      Author: george
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include "Utilities.h"
#include "NetworkDefs.h"

//TODO use data-types from NetworkDesf.h

class Network
{

	friend class ostream;

	public:

		/**
		 * @brief - Default Constructor for the Network Class
		 */
		Network();

		Network(Network* net);

		Network(const Network& net);

		Network(const ::std::vector< ::std::string>& nodes,
				 const EdgeVector& edges );

		virtual ~Network();

		Vertex addVertex(const std::string& name, const std::vector< Vertex >& parents = std::vector< Vertex>());

		void removeVertex(const Vertex& v);

		void removeVertex(const ::std::string& vertexName);

		bool isVertex(const ::std::string& vertexName);

		Vertex getVertex(const std::string& name);

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

		void getLeafNodes(::std::vector< ::std::string>& leafNodes);

		Graph& getGraph() {return this->graph;};

		void printGraph(std::ofstream& outf);

		VertexMap getVertexMap()  const {return this->vertexMap;};

		EdgeVector getEdgeVector()  const {return this->edges;};

		::std::vector < ::std::string> getVertexList();

		//::std::vector < ::std::string> getVertexList() ;

		int getDegree() const {return this->degree;};

		void setEdgeProperties(const Edge& e, const EdgeBundle& props);

		void setVertexProperties(const Vertex& v, const VertexBundle& props);

		const VertexBundle& getVertexProperties(const ::std::string& vertexName) const;

		const EdgeBundle& getEdgeProperties(const Edge& e) const;

		std::vector< ::std::string> getParents(const Vertex& v) ;

		//std::vector< ::std::string> getParents(const ::std::string& vertexName);

		std::vector< ::std::string> getParents(const ::std::string& vertexName) ;

		void setRequiredEdges( const EdgeVector& edges);

		void setProhibitedEdges( const EdgeVector& edges);

		void setNodeOrdering( const NodeOrdering& nodeOrdering);

		bool operator == (const Network& net);

		Network operator = (const Network& net);

		EdgeVector getRequiredEdges() const {return this->requiredEdges;};

		EdgeVector getProhibitedEdges() const {return this->prohibitedEdges;};

		NodeOrdering getNodeOrdering() const {return this->nodeOrdering;};

		Network* randomizeNetwork();

		bool isNetworkConsistent();

		bool isAcyclic();

		static Network*  generateRandomNetwork(const ::std::vector< ::std::string>& nodes,
												  const ::std::vector< ::std::string>& nodeOrdering = ::std::vector< ::std::string>(),
											      const ::std::vector< EdgePair>& requiredEdges = ::std::vector< EdgePair>(),
											      const ::std::vector< EdgePair>& prohibitedEdges = ::std::vector< EdgePair>());





	protected:

		bool isEdgeRequired(const EdgePair& edge);

		bool isEdgeProhibited(const EdgePair& edge);

		void getPossibleParents(const ::std::string& node, ::std::vector< ::std::string> nodes,
								   const NodeOrdering& nodeOrdering,
								   ::std::vector< ::std::string>& parents);

		bool checkForRequiredEdges();

		bool checkForProhibitedEdges();

		bool conflictingConstraints();

		bool conflictProhibitedRequired();

		bool conflictRequiredNodeOrdering();

		Vertex findLeafNode();

		void addRandomEdge( float probability);

		void removeRandomEdge( float probability);



	protected:

		int degree;

		Graph graph;

		VertexMap vertexMap;

		EdgeVector edges;

		NodeOrdering nodeOrdering;

		EdgeVector requiredEdges;

		EdgeVector prohibitedEdges;

		RandomNumberGenerator rand;

};

#endif /* NETWORK_H_ */
