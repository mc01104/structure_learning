/*
 * ADTree.cpp
 *
 *  Created on: 22 Feb 2013
 *      Author: george
 */

#include "ADTree.h"
#include "Dataset.h"

using namespace data;

ADTree::ADTree() : data()
{
	this->rootNode = new ADRootNode();
	this->rootNode->setName("root");
}

ADTree::~ADTree()
{
	this->destroyStructure();
}

void
ADTree::initialize(Dataset* data)
{
	this->data = data;

	this->indexMap = data->index;

	this->buildStructure();

	this->computeCounts();

}

int
ADTree::count(const QueryItem& query)
{
	return this->ADCount(this->rootNode, query);
}

int
ADTree::ADCount(ADNode* node, const QueryItem& query, int index)
{
	ADNode* currentADNode = node;

	if (index == query.size()) return currentADNode->getCount();

	VaryNode* varyNode;
	for (::std::vector<Node* >::iterator it = currentADNode->getChildren().begin(); it != currentADNode->getChildren().end(); ++it)
		if ((*it)->getName() == query[index].first)
		{
			varyNode = reinterpret_cast< VaryNode* >(*it);
			break;
		}

	ADNode* nextADNode;
	if (this->indexMap[query[index].first][2] == query[index].second)
	{
		for(::std::vector<Node* >::iterator it = varyNode->getChildren().begin(); it != varyNode->getChildren().end(); ++it)
		{
			if ((*it)->getName() == "NULL")
			{
				nextADNode =  reinterpret_cast< ADNode* > (*it);
				break;
			}
		}

	}
	else
	{
		for(::std::vector<Node* >::iterator it = varyNode->getChildren().begin(); it != varyNode->getChildren().end(); ++it)
		{

			if (reinterpret_cast< ADNode* >(*it)->getValue() == query[index].second)
			{
				nextADNode =  reinterpret_cast< ADNode* > (*it);
				break;
			}
		}

	}


	if (nextADNode->getName() == "NULL")
	{
		int count = this->ADCount(currentADNode, query,index + 1);
		::std::cout << "total:" << count << ::std::endl;
		//::std::cout << "number of siblings:" << nextADNode->getSiblings().size() << ::std::endl;
		for(::std::vector< Node*>::iterator it = nextADNode->getSiblings().begin(); it != nextADNode->getSiblings().end(); ++it)
		{
			//::std::cout << "sibling:" << (*it)->getName() << ::std::endl;
			count -= this->ADCount(reinterpret_cast< ADNode* >(*it), query, index + 1);
		}
		return  count;
	}

	if (nextADNode->getCount() == 0) return 0;

	return this->ADCount(nextADNode,query,index + 1);



}

void
ADTree::buildStructure()
{
       this->rootNode->buildStructure(data->index, data->valueMap);
}


void
ADTree::destroyStructure()
{
      delete rootNode;
}


void
data::ADTree::insertRecord(std::vector<int> record)
{
     this->rootNode->insertRecord(record);
}

void
data::ADTree::printTree()
{
	this->rootNode->print();
}

void
ADTree::computeCounts()
{
  for(::std::vector< ::std::vector< int> >::iterator it = this->data->dataDiscrete.begin(); it != this->data->dataDiscrete.end(); it++)
    this->insertRecord(*it);
}

