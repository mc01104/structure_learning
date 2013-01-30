/*
 * Verifier.h
 *
 *  Created on: 23 Jan 2013
 *      Author: george
 */

#ifndef VERIFIER_H_
#define VERIFIER_H_

#include "Network.h"

class Verifier
{
	public:
		Verifier();

		virtual ~Verifier();

		bool isAcyclic(Network& graph);
};

#endif /* VERIFIER_H_ */
