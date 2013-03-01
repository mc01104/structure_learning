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


Dataset::Dataset(const ::std::string& inputFile)
{
	this->inputFile = inputFile;

	this->loadData();

	this->discretizer->run(*this);

	this->computeTransposeData();

	this->buildIndexMap();

	this->buildADTree();

}

Dataset::~Dataset()
{

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
		int props[3];

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


int
Dataset::computeMCV(int index_elem, int arity)
{
	int currentMCV = 0;

	::std::vector< int> tmp;

	for(int i = 0; i < this->numberOfRecords; ++i)
		tmp.push_back(data[i][index_elem]);

	for(int i = 0; i < arity; ++i)
	{
		int counter = ::std::count(tmp.begin(),tmp.end(),i);

		currentMCV = ( counter > currentMCV ? counter : currentMCV);
	}

	return currentMCV;
}

void
Dataset::buildADTree()
{
	this->adtree.initialize(*this);
}

int
Dataset::count(const QueryItem& query)
{
	return this->adtree.count(query);
}


void
Dataset::computeTransposeData()
{
	for(int j = 0; j < nodes.size(); ++j)
	{
		::std::vector< double> tmp;
		for(int i = 0; i < this->numberOfRecords; ++i)
		{
			tmp.push_back(data[i][j]);
		}
		dataTransposed.push_back(tmp);
	}
}
