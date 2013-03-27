/*
 * Dataset.h
 *
 *  Created on: 22 Feb 2013
 *      Author: george
 */

#ifndef DATASET_H_
#define DATASET_H_

#include "ADTree.h"
#include "Discretizer.h"
#include <map>

namespace data
{

      class Dataset
      {
              public:
                      Dataset(const ::std::string& inputFile);

                      virtual ~Dataset();

                      void setDiscretizationAlgorithm(Discretizer* algorithm) {this->discretizer = algorithm;};

                      int count(const QueryItem& query);

                      //this has to be private ->who uses it?
                      void computeTransposeData();

                      void printIndexMap();

              private:

                      void loadData();

                      void buildIndexMap();

                      int computeMCV(int index_elem, int arity);

                      int computeArity(int indCol);

                      void buildADTree();

              public:
                      //make private and write getters
                       //use different data container to avoid unnecessary copies of the data
                      ::std::vector< ::std::vector<double> > data;

                      ::std::vector< ::std::vector<double> > dataTransposed;

                      ::std::vector< ::std::vector<int> > dataDiscrete;

                      ::std::vector< ::std::vector<int> > dataTransposedDiscrete;

                      ::std::vector< ::std::string> nodes;

                      ::std::map< ::std::string, int*> index;

              public:

                      int numberOfRecords;

                      ::std::string inputFile;

                      data::ADTree adtree;

                      Discretizer* discretizer;
      };
}

void test_dataset(const ::std::string& filename);

#endif /* DATASET_H_ */
