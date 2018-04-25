/*
 * Physics3D.h
 *
 *  Created on: Mar 1, 2018
 *      Author: wmagnus
 *
 */

#ifndef Physics3Dq_H_
#define Physics3Dq_H_

#include <Aspect.h>

class Physics3Dq : Aspect
{
public:
	Physics3Dq(Entity381 *ent);
	~Physics3Dq();

	void Tick(float dt);
};



#endif /* Physics3Dq_H_ */
