/*
 * Node.cpp
 *
 *  Created on: 1 Mar 2013
 *      Author: george
 */


#include "Node.h"

#include <sstream>
#include <iostream>

using namespace data;

Node::Node() :
	children(),
	name(),
	prev()
{
}

Node::~Node()
{
	for(::std::vector< Node*>::iterator it = children.begin(); it != children.end(); it++)
		delete *it;
}

void
Node::setName(const std::string& name)
{
	this->name = name;
}

void
Node::setParent(Node* n)
{
	this->prev = n;
}

std::string
Node::getName()
{
	return this->name;
}

std::vector<Node*>&
Node::getChildren()
{
	return this->children;
}

Node*
Node::addNextNode(Node* n)
{
	n->setParent(this);

	this->children.push_back(n);

	return n;
}

Node::Node(Node* n)
{
       this->children = n->getChildren();

       this->name = n->getName();

       this->prev = n->getParent();
}

Node*
Node::getParent()
{
	return this->prev;
}

ADNode::ADNode() :
		Node(),
		query(),
		count(0)
{
}

ADNode::~ADNode()
{
}

void ADNode::setCount(int count)
{
	this->count = count;
}

int
ADNode::getCount()
{
	return this->count;
}

void
ADNode::setQuery(const QueryItem& query)
{
	this->query = query;
}

const QueryItem&
ADNode::getQuery()
{
	return this->query;
}

ADNode::ADNode(ADNode* n):
    Node(n)
{
    this->query = n->getQuery();

    this->count = n->getCount();
}

Node*
ADNode::addNextNode(Node* n)
{
	Node* newNode = new VaryNode();

	return Node::addNextNode(newNode);
}

VaryNode::VaryNode() :
		Node()
{

}

VaryNode::~VaryNode()
{
}

VaryNode::VaryNode(VaryNode* n):
    Node(n)
{

}

Node*
VaryNode::addNextNode(Node* n)
{
	Node* newNode = new ADNode();

	return Node::addNextNode(newNode);
}

bool
ADRootNode::isRoot()
{
	return true;
}

void
ADNode::buildStructure(std::map< ::std::string, int*> index)
{
	if (this->name == "NULL") return;

    ::std::map< ::std::string, int*> tmp = index;

    for(::std::map< ::std::string, int* >::iterator it = tmp.begin(); it != tmp.end(); it++)
      {
        Node* n = this->addNextNode(new VaryNode());

        n->setName(it->first);
      }

    for (::std::vector<Node* >::iterator it = this->getChildren().begin(); it != this->getChildren().end(); ++it)
    {
    	(*it)->buildStructure(tmp);

    	tmp.erase(tmp.begin());
    }
}

void
ADNode::insertRecord(const std::vector<int>& record)
{
  for(::std::vector< Node*>::iterator it = this->children.begin(); it != this->children.end(); it++)
    {
      if(record[this->index] == this->value)
        this->incrementCounter();

      (*it)->insertRecord(record);
    }

  //return;
}

bool
ADNode::isRoot()
{
  return false;
}

void
VaryNode::buildStructure(std::map<std::string, int*> index)
{
    ::std::map< ::std::string, int*> tmp = index;

    int arity = index[this->name][1];

    int MCV = index[this->name][2];

    int ADIndex = index[this->getName()][0];

    Node* n;

    for(int i = 0; i < arity; i++)
      {
        n = this->addNextNode(new ADNode());

        if( i != MCV)
          {
            ::std::stringstream ss;

            ss << i;

            n->setName(ss.str());

            reinterpret_cast< ADNode*>(n)->setValue(i);

            reinterpret_cast< ADNode*>(n)->setIndex(ADIndex);
          }

        else
            n->setName("NULL");
      }

    tmp.erase(tmp.begin());

    for (::std::vector<Node* >::iterator it = this->getChildren().begin(); it != this->getChildren().end(); ++it)
    	(*it)->buildStructure(tmp);


}

void
VaryNode::insertRecord(const std::vector<int>& record)
{
    for(::std::vector< Node*>::iterator it = this->children.begin(); it != this->children.end(); it++)
      (*it)->insertRecord(record);

    //return;
}

bool
VaryNode::isRoot()
{
  return false;
}

void
ADRootNode::insertRecord(const std::vector<int>& record)
{
  for(::std::vector< Node*>::iterator it = this->children.begin(); it != this->children.end(); it++)
    (*it)->insertRecord(record);

  //return;
}

void
ADNode::incrementCounter()
{
  this->count++;
}

void
Node::print()
{
	::std::cout << this->getName() << ::std::endl;
	for(::std::vector<Node* >::iterator it = this->getChildren().begin(); it != this->getChildren().end(); ++it)
		(*it)->print();

}








