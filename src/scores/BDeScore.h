/*
 * BDeScore.h
 *
 *  Created on: 18 Nov 2013
 *      Author: george
 */

#ifndef BDESCORE_H_
#define BDESCORE_H_

#include "Score.h"

class BDeScore: public DecomposableScore
{
	public:

		BDeScore();

		virtual ~BDeScore();

		virtual double computeSubGrachScore(Network& net, const data::Dataset& data, const SubGraph& subgraph);

};

#endif /* BDESCORE_H_ */
