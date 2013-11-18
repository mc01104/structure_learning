/*
 * MDLScore.h
 *
 *  Created on: 18 Nov 2013
 *      Author: george
 */

#ifndef MDLSCORE_H_
#define MDLSCORE_H_

#include "Score.h"

class MDLScore: public DecomposableScore
{
	public:
		MDLScore();

		virtual ~MDLScore();

	protected:

		virtual double computeSubGraphScore(Network& net, const data::Dataset& data, const SubGraph& subgraph);
};

#endif /* MDLSCORE_H_ */
