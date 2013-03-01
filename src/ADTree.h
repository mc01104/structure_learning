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

typedef struct
{
	::std::vector< void*> children;

	::std::string name;
} VaryNode;

typedef struct
{
	::std::vector<void*> children;

	::std::string name;

	int count;
}ADNode;

typedef ::std::vector< ::std::pair< ::std::string, int> > QueryItem;

class Dataset;

class ADTree
{
	public:
		ADTree();

		virtual ~ADTree();

	private:
		::std::vector<VaryNode> VNodes;

		::std::vector<ADNode> ADNodes;

		ADNode* rootNode;


	public:
		void initialize(Dataset& data);

		int count(const QueryItem& query);
};

#endif /* ADTREE_H_ */
