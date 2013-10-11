//============================================================================
// Name        : test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "stdlib.h"
#include "stdio.h"
#include <tinyxml.h>
#include <vector>
#include "ProblemFactory.h"
#include "solvers/SolverFactory.h"
#include "Problem.h"
#include "Network.h"
#include "Utilities.h"

#include "data/Dataset.h"

using namespace std;

bool test_graph();

bool test_random();

//bool test_data();

int main(int argc, char* argv[])
{
    test_graph();

    //test_dataset("../src/data/data.txt");
	//test_random();

	return 0;
}

bool test_random()
{
	RandomNumberGenerator* rand = new RandomNumberGenerator();

	for( int i = 0; i < 20; i++)
	{
		::std::cout << "iteration : " << i << endl;
		::std::cout << "random float :" << rand->randFloat(0,1) << endl;
		::std::cout << "random int :" << rand->randInt(0,6) << endl;
	}

	return true;
}

bool test_graph()
{

		::std::ofstream myfile;
		myfile.open("net");
		::std::vector< ::std::string> nodes;
		nodes.push_back("George");
		nodes.push_back("Mpampis");
		nodes.push_back("Spyros");
		nodes.push_back("Kwstas");
		nodes.push_back("Dimitris");
		nodes.push_back("Giannis");

		::std::vector<EdgePair> prohibited, required;
		prohibited.push_back(EdgePair("Dimitris","Kwstas"));
//		prohibited.push_back(EdgePair("Mpampis","George"));

		required.push_back(EdgePair("Mpampis", "George"));
//		Network* net = new Network(nodes,required);
		NodeOrdering ordering;
		//ordering.push_back("George");
		ordering.push_back("Mpampis");
		ordering.push_back("Spyros");
		ordering.push_back("Giannis");

		try
		{
			Network* net = Network::generateRandomNetwork(nodes,ordering,required,prohibited);
			::std::cout << "number of edges :" << net->getNumEdges() << ::std::endl;
			::std::cout << "number of vertices :" << net->getNumVertices() << ::std::endl;
			net->printGraph(myfile);
		}
		catch(::std::string& e)
		{
			::std::cout << e << ::std::endl;
		}


//
		myfile.close();

        return true;
}
