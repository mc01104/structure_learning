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

                    const ::std::string& getName();

                    virtual Node* addNextNode(Node* n);

                    virtual const ::std::vector<Node* >& getChildren();

                    Node* getParent();

            protected:

                    ::std::vector< Node*> children;

                    ::std::string name;

                    Node* prev;

    };


    class ADNode : public Node
    {
                    QueryItem query;

                    int count;

            public:

                    ADNode();

                    ADNode(ADNode* n);

                    ~ADNode();

                    void setCount(int count);

                    int getCount();

                    void setQuery(const QueryItem& query);

                    const QueryItem& getQuery();

                    virtual Node* addNextNode(Node* n);

                    virtual bool isRoot();
    };


    class VaryNode : public Node
    {
            public:

                    VaryNode();

                    VaryNode(VaryNode* n);

                    ~VaryNode();

                    virtual Node* addNextNode(Node* n);

                    virtual bool isRoot();
    };


    class ADRootNode : public ADNode
    {
            public:

                    virtual bool isRoot();
    };
}
#endif /* NODE_H_ */
