/*
 * Discretizer.h
 *
 *  Created on: 22 Feb 2013
 *      Author: george
 */

#ifndef DISCRETIZER_H_
#define DISCRETIZER_H_

namespace data
{
      class Dataset;

      class Discretizer
      {
              public:
                      Discretizer();

                      virtual ~Discretizer();

                      virtual void run(Dataset& data) = 0;

      };
}

#endif /* DISCRETIZER_H_ */
