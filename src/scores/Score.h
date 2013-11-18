/*
 * Score.h
 *
 *  Created on: 16 Nov 2013
 *      Author: george
 */

#ifndef SCORE_H_
#define SCORE_H_

#include "../NetworkDefs.h"
#include "../Network.h"

#include "../data/Dataset.h"


/**
 * @brief Interface class for Scores of Bayesian Networks
 * @author Georgios Fagogenis
 * @date 2013/11/18
 */

class Score
{
	public:

		Score();

		virtual ~Score();

		/**
		 * Pure virtual function - computes the score of a graph given the data
		 * @param net - bayesian network under evaluation
		 * @param data - dataset holding the data for the structure learning experiment
		 * @return
		 */
		virtual double computeScore( Network& net, const data::Dataset& data) = 0;

};

/**
 * @brief Subclass of Score implementing interface for decomposable scores of Bayesian Networks
 * @author Georgios Fagogenis
 * @date 2013/11/18
 */

class DecomposableScore : public Score
{
	public:

		DecomposableScore();

		virtual ~DecomposableScore();

		/**
		 * Pure virtual function - computes the score of a graph given the data
		 * @param net - bayesian network under evaluation
		 * @param data - dataset holding the data for the structure learning experiment
		 * @return
		 */
		virtual double computeScore(Network& net, const data::Dataset& data);

	protected:

		void addSubGraphToHash(SubGraph graph, double score);

		virtual double computeSubGraphScore(Network& net, const data::Dataset& data, const SubGraph& subgraph) = 0;
};

#endif /* SCORE_H_ */
