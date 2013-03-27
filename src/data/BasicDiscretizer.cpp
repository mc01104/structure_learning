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
        //redundant runs in the dataset constructor
	data.computeTransposeData();

	data.dataTransposedDiscrete.resize(data.nodes.size());

	for(size_t i = 0; i < data.nodes.size(); ++i)
		this->columnDiscretizer(data,i);
//::std::cout << "column discretizer finished" << ::std::endl;
	//write a general transpose vector function
        for(int j = 0; j < data.numberOfRecords; ++j)
        {
                ::std::vector< int> tmp;
                for(size_t i = 0; i < data.nodes.size(); ++i)
                {
                        tmp.push_back(data.dataTransposedDiscrete[i][j]);
                }
                data.dataDiscrete.push_back(tmp);
        }
//::std::cout << "transposed finished" << ::std::endl;
}

void
BasicDiscretizer::columnDiscretizer(Dataset& data,int column, int numOfBins)
{
	::std::vector<double> tmp = data.dataTransposed[column];

	::std::vector<int> tmpDiscrete(tmp.size());

	double min = *(::std::min_element(tmp.begin(),tmp.end()));
	double max = *(::std::max_element(tmp.begin(),tmp.end()));

	double binSize = this->computeBinSize(min,max,numOfBins);

	for(size_t i = 0; i < tmp.size(); ++i)
	{
		tmpDiscrete[i] = this->binValue(tmp[i],min,binSize);
	}

	::std::cout << "min:" << min << ::std::endl;

	::std::cout << "max" << max << ::std::endl;

	::std::cout << "bin size:" << binSize << ::std::endl;
//::std::cout << "vgike" << ::std::endl;
	data.dataTransposedDiscrete[column] = tmpDiscrete;
//	::std::cout << "data transposition success" << ::std::endl;

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
	k = static_cast<int>((value- min)/binSize);
	::std::cout << "value   :" << value << " ---- int :" << k << ::std::endl;
	return k;

}




