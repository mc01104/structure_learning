/*
 * BasicDiscretizer.cpp
 *
 *  Created on: 22 Feb 2013
 *      Author: george
 */

#include "BasicDiscretizer.h"
#include "Dataset.h"
#include <iostream>
#include <algorithm>

using namespace data;

BasicDiscretizer::BasicDiscretizer() :
	Discretizer()
{

}

BasicDiscretizer::~BasicDiscretizer()
{

}

void
BasicDiscretizer::run(Dataset& data)
{

	data.getDataTransposedDiscrete().resize(data.getNodes().size());

	for(size_t i = 0; i < data.getNodes().size(); ++i)
		this->columnDiscretizer(data,i);

        for(int j = 0; j < data.getNumberOfRecords(); ++j)
        {
                ::std::vector< int> tmp;
                for(size_t i = 0; i < data.getNodes().size(); ++i)
                        tmp.push_back(data.getDataTransposedDiscrete()[i][j]);

                data.getDataDiscrete().push_back(tmp);
        }

}

void
BasicDiscretizer::columnDiscretizer(Dataset& data,int column, int numOfBins)
{
	::std::vector<double> tmp = data.getDataTransposed()[column];

	::std::vector<int> tmpDiscrete(tmp.size());

	double min = *(::std::min_element(tmp.begin(),tmp.end()));
	double max = *(::std::max_element(tmp.begin(),tmp.end()));

	double binSize = this->computeBinSize(min,max,numOfBins);

	for(size_t i = 0; i < tmp.size(); ++i)
		tmpDiscrete[i] = this->binValue(tmp[i],min,binSize);

	data.getDataTransposedDiscrete()[column] = tmpDiscrete;

}

double
BasicDiscretizer::computeBinSize(double min, double max, int numOfBins)
{
	return static_cast<double>((max - min)/numOfBins);
}

int
BasicDiscretizer::binValue(double value, double min, double binSize)
{
	return static_cast<int>((value - min)/binSize);
}




