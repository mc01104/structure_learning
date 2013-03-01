/*
 * BasicDiscretizer.cpp
 *
 *  Created on: 22 Feb 2013
 *      Author: george
 */

#include "BasicDiscretizer.h"
#include "Dataset.h"

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
	data.computeTransposeData();

	for(size_t i = 0; i < data.nodes.size(); ++i)
		this->columnDiscretizer(data,i);
}

void
BasicDiscretizer::columnDiscretizer(Dataset& data,int column, int numOfBins)
{
	::std::vector<double> tmp = data.dataTransposed[column];

	::std::vector<int> tmpDiscrete(tmp.size());

	double min = *(::std::min(tmp.begin(),tmp.end()));
	double max = *(::std::max(tmp.begin(),tmp.end()));

	double binSize = this->computeBinSize(min,max,numOfBins);

	for(size_t i = 0; i < tmp.size(); ++i)
	{
		tmpDiscrete[i] = this->binValue(tmp[i],min,binSize);
	}


	data.dataTransposedDiscrete[column] = tmpDiscrete;
}

double
BasicDiscretizer::computeBinSize(double min, double max, int numOfBins)
{
	return static_cast<double>((max - min)/numOfBins);
}

int
BasicDiscretizer::binValue(double value, double min, double binSize)
{
	int k = 1;

	while(value > min + k*binSize) k++;

	return k;

}




