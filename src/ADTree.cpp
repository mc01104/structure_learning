/*
 * ADTree.cpp
 *
 *  Created on: 22 Feb 2013
 *      Author: george
 */

#include "ADTree.h"

ADTree::ADTree()
{
	this->rootNode = new ADNode();
	this->rootNode->name = "root";
}

ADTree::~ADTree()
{

}

void
ADTree::initialize(Dataset& data)
{

}

int
ADTree::count(const QueryItem& query)
{
	return 1;
}
