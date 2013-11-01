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

	//this->computeCounts();

}

int
ADTree::count(const QueryItem& query)
{
	return 1;
}

void
ADTree::buildStructure()
{
       this->rootNode->buildStructure(data->index);
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

