/*
 * Node.h
 *
 *  Created on: 1 Mar 2013
 *      Author: george
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <string>
#include <map>

typedef ::std::vector< ::std::pair< ::std::string, int> > QueryItem;

namespace data
{
    class Node
    {
            public:

                    Node();

                    Node(Node* n);

                    virtual ~Node();

                    virtual bool isRoot() = 0;

                    void setName(const std::string& name);

                    void setParent(Node* n);

                    ::std::string getName();

                    virtual Node* addNextNode(Node* n);

                    virtual ::std::vector<Node* >& getChildren();

                    Node* getParent();

                    ::std::vector< Node* >& getSiblings();

                    virtual void buildStructure(const ::std::map< ::std::string, int*>& index, const ::std::map< ::std::string, ::std::vector<int> >& valueMap) = 0;

                    virtual void insertRecord( const::std::vector< int>& record) = 0;

                    virtual void print();

            protected:

                    ::std::vector< Node*> children;

                    ::std::vector< Node*> siblings;

                    ::std::string name;

                    Node* prev;

    };


    class ADNode : public Node
    {
                    int count;

                    int index;

                    int value;

            public:

                    ADNode();

                    ADNode(ADNode* n);

                    virtual ~ADNode();

                    void setCount(int count);

                    int getCount();

                    virtual Node* addNextNode(Node* n);

                    virtual void buildStructure(const ::std::map< ::std::string, int*>& index, const ::std::map< ::std::string, ::std::vector<int> >& valueMap);

                    virtual void insertRecord( const ::std::vector< int>& record);

                    virtual bool isRoot();

                    virtual void print();

                    void setIndex(int index) {this->index = index;};

                    void setValue(int value) {this->value = value;};

                    int getIndex() {return this->index;};

                    int getValue() {return this->value;};

            protected:
                    void incrementCounter();
    };


    class VaryNode : public Node
    {
            public:

                    VaryNode();

                    VaryNode(VaryNode* n);

                    virtual ~VaryNode();

                    virtual Node* addNextNode(Node* n);

                    virtual void buildStructure(const ::std::map< ::std::string, int*>& index, const ::std::map< ::std::string, ::std::vector<int> >& valueMap);

                    virtual void insertRecord( const ::std::vector< int>& record);

                    virtual bool isRoot();

    };


    class ADRootNode : public ADNode
    {
            public:

                    virtual bool isRoot();

                    virtual void insertRecord( const ::std::vector< int>& record );

    };
}
#endif /* NODE_H_ */
