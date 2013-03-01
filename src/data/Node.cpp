/*
 * Node.cpp
 *
 *  Created on: 1 Mar 2013
 *      Author: george
 */


#include "Node.h"

#include <sstream>

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

const std::string&
Node::getName()
{
	return this->name;
}

const std::vector<Node*>&
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
	Node* newNode = new VaryNode( reinterpret_cast< VaryNode*>(n));

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
	Node* newNode = new ADNode( reinterpret_cast< ADNode* > (n));

	return Node::addNextNode(newNode);
}

bool
ADRootNode::isRoot()
{
	return true;
}

void
data::ADNode::buildStructure(std::map< ::std::string, int*> index)
{
    ::std::map< ::std::string, int*> tmp = index;

    for(::std::map< ::std::string, int* >::iterator it = tmp.begin(); it != tmp.end(); it++)
      {
        Node* n = this->addNextNode(new VaryNode());

        n->setName(it->first);

        n->buildStructure(tmp);
      }
}

void
data::ADNode::insertRecord(const std::vector<int>& record)
{
  for(::std::vector< Node*>::iterator it = this->children.begin(); it != this->children.end(); it++)
    {
      if(record[this->index] == this->value)
        this->incrementCounter();
      (*it)->insertRecord(record);
    }
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

        if( arity != MCV)
          {
            ::std::stringstream ss;

            ss << i;

            n->setName(ss.str());

            reinterpret_cast< ADNode*>(n)->setValue(i);

            reinterpret_cast< ADNode*>(n)->setIndex(ADIndex);

            tmp.erase(tmp.begin());

            n->buildStructure(tmp);
          }
        else
          {
            n->setName("NULL");
          }
      }
}

void
VaryNode::insertRecord(const std::vector<int>& record)
{
    for(::std::vector< Node*>::iterator it = this->children.begin(); it != this->children.end(); it++)
      (*it)->insertRecord(record);
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
}

void
ADNode::incrementCounter()
{
  this->count++;
}







