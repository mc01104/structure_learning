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

        Network* g = new Network();

        g->addVertex("George");
        g->addVertex("Spyros");
        g->addVertex("Mpampis");

        g->addEdge(g->getVertex("George"),g->getVertex("Mpampis"));
        g->addEdge(g->getVertex("Mpampis"),g->getVertex("Spyros"));

        if (Network::isAcyclic(g))
                cout << "graph is acyclic" << endl;
        else
                cout << "graph is cyclic" << endl;

        g->addEdge("Spyros","George");

        if (Network::isAcyclic(g))
                cout << "graph is acyclic" << endl;
        else
                cout << "graph is cyclic" << endl;


        return true;
}
