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
                      ::std::vector<VaryNode> VNodes;

                      ::std::vector<ADNode> ADNodes;

                      ADRootNode* rootNode;

                      const Dataset* data;

              public:

                      void initialize(Dataset* data);

                      int count(const QueryItem& query);

              private:

                      void buildStructure();

                      void destroyStructure();

                      void computeCounts();

      };
}
#endif /* ADTREE_H_ */
