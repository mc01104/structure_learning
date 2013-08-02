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

#include "data/Dataset.h"

using namespace std;

bool test_graph();

//bool test_data();

int main(int argc, char* argv[])
{
         test_graph();

         //test_data();

    return 0;
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

		Network net = Network::generateRandomNetwork(nodes);

		::std::cout << "number of edges :" << net.getNumEdges() << ::std::endl;
		::std::cout << "number of vertices :" << net.getNumVertices() << ::std::endl;
		net.printGraph(myfile);

		myfile.close();

        return true;
}
