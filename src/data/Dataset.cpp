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

	//this->adtree.printTree();

	this->printData();

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

	this->valueMap[this->nodes[indCol]] = ::std::vector<int> (tmp.begin(),tmp.end());

	return tmp.size();
}



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

  data.printIndexMap();

  QueryItem query;
//  query.push_back(::std::pair< ::std::string, int>("george",2));
  query.push_back(::std::pair< ::std::string, int>("mpampis",0));
  ::std::cout << "counts:" << data.count(query) << ::std::endl;
}

void
Dataset::printData()
{

	for(int i = 0; i < this->numberOfRecords; ++i)
	{
		for(::std::vector<int>::iterator it = this->dataDiscrete[i].begin(); it != this->dataDiscrete[i].end(); ++it)
			::std::cout << *it << " ";

		::std::cout << ::std::endl;
	}

}

