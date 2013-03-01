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

class Dataset
{
	public:
		Dataset(const ::std::string& inputFile);

		virtual ~Dataset();

		void setDiscretizationAlgorithm(Discretizer* algorithm) {this->discretizer = algorithm;};

		int count(const QueryItem& query);

		void computeTransposeData();

	private:

		void loadData();

		void buildIndexMap();

		int computeMCV(int index_elem, int arity);

		int computeArity(int indCol);

		void buildADTree();

	public:

		::std::vector< ::std::vector<double> > data;

		::std::vector< ::std::vector<double> > dataTransposed;

		::std::vector< ::std::vector<int> > dataDiscrete;

		::std::vector< ::std::vector<int> > dataTransposedDiscrete;

		::std::vector< ::std::string> nodes;

		::std::map< ::std::string, int*> index;

	private:

		int numberOfRecords;

		::std::string inputFile;

		ADTree adtree;

		Discretizer* discretizer;
};

#endif /* DATASET_H_ */
