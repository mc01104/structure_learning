/*
 * ADTree.cpp
 *
 *  Created on: 22 Feb 2013
 *      Author: george
 */

#include "ADTree.h"

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

	this->buildStructure();

	this->computeCounts();

}

int
ADTree::count(const QueryItem& query)
{
	return 1;
}

void
ADTree::buildStructure()
{

}


void
ADTree::destroyStructure()
{

}


void
ADTree::computeCounts()
{

}

