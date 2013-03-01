/*
 * BasicDiscretizer.h
 *
 *  Created on: 22 Feb 2013
 *      Author: george
 */

#ifndef BASICDISCRETIZER_H_
#define BASICDISCRETIZER_H_

#include "Discretizer.h"

class BasicDiscretizer: public Discretizer
{
	public:
		BasicDiscretizer();

		virtual ~BasicDiscretizer();

		virtual void run(Dataset& data);

	private:

		void columnDiscretizer(Dataset& data,int column, int numOfBins = 8);

		double computeBinSize(double min, double max, int numOfBins);

		int binValue(double value, double min, double binSizemax);
};

#endif /* BASICDISCRETIZER_H_ */
