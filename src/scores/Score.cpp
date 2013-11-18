/*
 * Score.cpp
 *
 *  Created on: 16 Nov 2013
 *      Author: george
 */

#include <vector>

#include "Score.h"

Score::Score()
{
}

Score::~Score()
{
}

DecomposableScore::DecomposableScore() :
		Score()
{
}

DecomposableScore::~DecomposableScore()
{
}

double
DecomposableScore::computeScore( Network& net, const data::Dataset& data)
{
	double score = 0;

	for( ::std::vector< ::std::string>::iterator it = net.getVertexList().begin(); it != net.getVertexList().end(); ++it)
	{
		SubGraph tmp(*it,net.getParents(*it));

		score += this->computeSubGraphScore(net, data, tmp);

		this->addSubGraphToHash(tmp, score);
	}

	return score;
}

void
DecomposableScore::addSubGraphToHash(SubGraph graph, double score)
{
}


