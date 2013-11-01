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

#include "Node.h"

namespace data
{
      class Dataset;

      class ADTree
      {
              public:
                      ADTree();

                      virtual ~ADTree();

              private:

                      ADRootNode* rootNode;

                      Dataset* data;

                      ::std::map< ::std::string, int*> indexMap;

              public:

                      void initialize(Dataset* data);

                      int count(const QueryItem& query);

                      void insertRecord(::std::vector<int> record);

                      void printTree();

              private:

                      void buildStructure();

                      void destroyStructure();

                      void computeCounts();

      };
}
#endif /* ADTREE_H_ */
