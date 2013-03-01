/*
 * ADTree.h
 *
 *  Created on: 22 Feb 2013
 *      Author: george
 */

#ifndef ADTREE_H_
#define ADTREE_H_

#include <vector>
#include <string>


typedef ::std::vector< ::std::pair< ::std::string, int> > QueryItem;
class Dataset;

class Node
{
	public:

		Node();

		virtual ~Node();

		virtual bool isRoot() = 0;

		void setName(const std::string& name);

		void setParent(Node* n);

		const ::std::string& getName();

		virtual Node* addNextNode(Node* n) = 0;

		virtual const std::vector<Node* >& getChildren();

		Node* getParent();

	private:

		::std::vector< void*> children;

		::std::string name;

		Node* prev;

};


class ADNode : public Node
{
		QueryItem query;

		int count;

	public:

		ADNode();

		~ADNode();

		virtual Node* addNextNode(Node* n);
};


class VaryNode : public Node
{
	public:

		VaryNode();

		~VaryNode();

		virtual Node* addNextNode(Node* n);
};


class ADRootNode : public ADNode
{
	public:

		virtual bool isRoot();
};

class ADTree
{
	public:
		ADTree();

		virtual ~ADTree();

	private:
		::std::vector<VaryNode> VNodes;

		::std::vector<ADNode> ADNodes;

		ADRootNode* rootNode;

		Dataset& data;

	public:

		void initialize(const Dataset& data);

		int count(const QueryItem& query);

	private:

		void buildStructure();

		void computeCounts();

};

#endif /* ADTREE_H_ */
