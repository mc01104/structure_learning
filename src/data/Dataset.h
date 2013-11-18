/**
 * Dataset.h
 *
 *@date
 *@author george
 */

#ifndef DATASET_H_
#define DATASET_H_

#include <map>
#include <vector>
#include <set>

#include "ADTree.h"
#include "Discretizer.h"

namespace data
{
	  /**
	   * @brief This class is used to store the data samples in a matrix representation
	   * @details This class is used to store the data samples. A Discretizer is applied on the data after loading them from a text file.
 	   * An AD-Tree is built to ensure efficient querying of the dataset. This is later used for computing sufficient statistics
	   * @author Georgios Fagogenis
	   * @date 2013/11/01
	   */
      class Dataset
      {
              public:
    	  	  	  	  /**
    	  	  	  	   * This is the constructor for the Dataset class
    	  	  	  	   * @param inputFile string variable holding the full path to the data file
    	  	  	  	   */
                      Dataset(const ::std::string& inputFile);

                      /**
                       * Class destructor
                       */
                      virtual ~Dataset();

                      /**
                       * This function is used to set the discretization algorithm
                       * @param algorithm discretization algorithm
                       */
                      void setDiscretizationAlgorithm(Discretizer* algorithm) {this->discretizer = algorithm;};

                      /**
                       * This function is used to count the instances that match a specific query in the dataset
                       * @param query vector of parameter-value std::pairs. Parameters are strings, values are integers
                       * @return integer number of occurrences of the input query within the dataset
                       */
                      int count(const QueryItem& query);

                      /**
                       * prints the index, the arity and the most common value for each column (node) of the dataset.
                       * Mainly for debugging
                       */
                      void printIndexMap();

                      int getNumberOfRecords() { return this->numberOfRecords;};

              private:

                      void loadData();

                      void buildIndexMap();

                      int computeMCV(int index_elem, int arity);

                      int computeArity(int indCol);

                      void buildADTree();

                      void computeTransposeData();

                      void printData();

              public:

                      const ::std::map< ::std::string, int*>& getIndex() {return this->index;};

                      const ::std::map< ::std::string, ::std::vector<int> >& getValueMap() {return this->valueMap;};

                      ::std::vector< ::std::vector<int> >& getDataDiscrete() {return this->dataDiscrete;};

                      ::std::vector< ::std::vector<int> >& getDataTransposedDiscrete() {return this->dataTransposedDiscrete;};

                      ::std::vector< ::std::vector<double> >& getData() {return this->data;};

                      ::std::vector< ::std::vector<double> >& getDataTransposed() {return this->dataTransposed;};

                      const ::std::vector< ::std::string>& getNodes() {return this->nodes;};

              private:
                      ::std::vector< ::std::vector<double> > data;

                      ::std::vector< ::std::vector<double> > dataTransposed;

                      ::std::vector< ::std::vector<int> > dataDiscrete;

                      ::std::vector< ::std::vector<int> > dataTransposedDiscrete;

                      ::std::vector< ::std::string> nodes;

                      ::std::map< ::std::string, int*> index;

                      ::std::map< ::std::string, ::std::vector<int> > valueMap;


                      int numberOfRecords;

                      ::std::string inputFile;

                      data::ADTree adtree;

                      Discretizer* discretizer;
      };
}

void test_dataset(const ::std::string& filename);

#endif /* DATASET_H_ */
