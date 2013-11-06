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
	name("g"),
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

	for (::std::vector< Node*>::iterator it = this->children.begin(); it != this->children.end(); ++it)
	{
		(*it)->getSiblings().push_back(n);
		n->getSiblings().push_back((*it));
	}

	this->children.push_back(n);

	return n;
}

Node::Node(Node* n)
{
       this->children = n->getChildren();

       this->siblings = n->getSiblings();

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


ADNode::ADNode(ADNode* n):
    Node(n)
{
	this->index = n->getIndex();

    this->count = n->getCount();

	this->value = n->getValue();
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
ADNode::buildStructure(const ::std::map< ::std::string, int*>& index, const ::std::map< ::std::string, ::std::vector<int> >& valueMap)
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
    	(*it)->buildStructure(tmp, valueMap);

    	tmp.erase(tmp.begin());
    }
}

void
ADNode::insertRecord(const std::vector<int>& record)
{
	if (this->getName() == "NULL") return;

    if(record[this->index] == this->value)
    	this->incrementCounter();
    else
    	return;

	for(::std::vector< Node*>::iterator it = this->children.begin(); it != this->children.end(); it++)
       (*it)->insertRecord(record);

}

bool
ADNode::isRoot()
{
  return false;
}

void
VaryNode::buildStructure(const ::std::map< ::std::string, int*>& index, const ::std::map< ::std::string, ::std::vector<int> >& valueMap)
{
    ::std::map< ::std::string, int*> tmp = index;

    int arity = index.at(this->name)[1];

    int MCV = index.at(this->name)[2];

    int ADIndex = index.at(this->getName())[0];

    Node* n;
    for(int i = 0; i < arity; i++)
      {
        n = this->addNextNode(new ADNode());

        int value = valueMap.at(this->name)[i];

        if(value != MCV)
          {
            ::std::stringstream ss;

            ss << value;

            n->setName(ss.str());

            reinterpret_cast< ADNode*>(n)->setValue(value);

            reinterpret_cast< ADNode*>(n)->setIndex(ADIndex);
          }

        else
            n->setName("NULL");
      }

    tmp.erase(tmp.begin());

    for (::std::vector<Node* >::iterator it = this->getChildren().begin(); it != this->getChildren().end(); ++it)
    	(*it)->buildStructure(tmp, valueMap);


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
  ADNode::incrementCounter();

  for(::std::vector< Node*>::iterator it = this->children.begin(); it != this->children.end(); it++)
    (*it)->insertRecord(record);

}

void
ADNode::incrementCounter()
{
  this->count++;
}

void
ADNode::print()
{
	::std::cout << "node counter:" << this->getCount() << ::std::endl;

	::Node::print();
}

::std::vector<Node* >&
 Node::getSiblings()
{
	return this->siblings;

}

void
Node::print()
{
	::std::cout << this->getName() << ::std::endl;
	for(::std::vector<Node* >::iterator it = this->getChildren().begin(); it != this->getChildren().end(); ++it)
		(*it)->print();

}
