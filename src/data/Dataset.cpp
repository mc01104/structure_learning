/*
 * Dataset.cpp
 *
 *  Created on: 22 Feb 2013
 *      Author: george
 */

#include "Dataset.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>

#include "BasicDiscretizer.h"

using namespace data;

Dataset::Dataset(const ::std::string& inputFile) :
    discretizer()
{
	this->inputFile = inputFile;

	::std::cout << this->inputFile << ::std::endl;

	this->loadData();

	this->computeTransposeData();

	this->discretizer = new BasicDiscretizer();

	this->discretizer->run(*this);

	this->buildIndexMap();

	this->buildADTree();

}

Dataset::~Dataset()
{
        delete discretizer;

        for(::std::map< ::std::string, int* >::iterator it = index.begin(); it != index.end(); it++)
            delete[] it->second;
}


void
Dataset::loadData()
{
	::std::ifstream file(this->inputFile.c_str());

	this->numberOfRecords = 0;

	::std::string line;

	if(file.is_open())
	{

		::std::getline(file,line);

		{
			::std::istringstream ss(line);

			while(ss)
			{
				::std::string s;

				if(!::std::getline(ss,s,',')) break;

				nodes.push_back(s);
			}

		}

		while(file.good())
		{

			::std::getline(file,line);

			::std::istringstream ss(line);

			::std::vector< double> record;

			while(ss)
			{
				::std::string s;

				if(!::std::getline(ss,s,',')) break;

				record.push_back(atoi(s.c_str()));
			}

			data.push_back(record);

			this->numberOfRecords++;
		}
	}

}

//FIXED
void
Dataset::buildIndexMap()
{
	int index_elem = 0;

	int arity = 0;

	int MCV = 0;

	for(::std::vector< ::std::string>::iterator it = this->nodes.begin(); it != this->nodes.end(); ++it)
	{
		int* props = new int[3];

		arity = this->computeArity(index_elem);

		MCV = this->computeMCV(index_elem,arity);

		props[0] = index_elem++; props[1] = arity; props[2] = MCV;

		index[*it] =props;
	}
}


int
Dataset::computeArity(int indCol)
{
	::std::set<int> tmp;

	for(int i = 0; i < this->numberOfRecords; ++i)
	{
		int value = dataDiscrete[i][indCol];

		tmp.insert(value);
	}
	return tmp.size();
}


//this is not going to work - FIX! ---> FIXED
int
Dataset::computeMCV(int index_elem, int arity)
{
	::std::vector< int> tmp = this->dataTransposedDiscrete[index_elem];

	::std::vector< int> counterVector;

	for(int i = 0; i < 9; ++i)
		counterVector.push_back(::std::count(tmp.begin(),tmp.end(),i));

	return ::std::distance(counterVector.begin(),::std::max_element(counterVector.begin(),counterVector.end()));
}

void
data::Dataset::printIndexMap()
{
        for(::std::map< ::std::string, int*>::iterator it = this->index.begin(); it != this->index.end(); ++it)
            ::std::cout << "name:" << it->first << "   index:" << it->second[0] << "   arity:" << it->second[1] << "   MCV:" << it->second[2] << ::std::endl;

}

void
Dataset::buildADTree()
{
	this->adtree.initialize(this);
}

int
Dataset::count(const QueryItem& query)
{
	return this->adtree.count(query);
}

//write a general purpose transpose function
void
Dataset::computeTransposeData()
{
	for(size_t j = 0; j < nodes.size(); ++j)
	{
		::std::vector< double> tmp;
		for(int i = 0; i < this->numberOfRecords; ++i)
		{
			tmp.push_back(data[i][j]);
		}
		dataTransposed.push_back(tmp);
	}
}

void test_dataset(const ::std::string& filename)
{
  ::std::cout << "test_dataset" << ::std::endl;

  Dataset data(filename);

  ::std::cout << data.data[1][1] << ::std::endl;
//  ::std::cout << data.data[3][1] << ::std::endl;
//  ::std::cout << data.data[3][2] << ::std::endl;
//
////  ::std::cout << "...and now the transposed" << ::std::endl;
////  ::std::cout << data.dataTransposed[1][1] << ::std::endl;
////   ::std::cout << data.dataTransposed[1][3] << ::std::endl;
////   ::std::cout << data.dataTransposed[2][3] << ::std::endl;
//
  for(::std::vector< ::std::string>::iterator it = data.nodes.begin(); it != data.nodes.end(); ++it)
    ::std::cout << *it << ::std::endl;

  data.printIndexMap();
}
