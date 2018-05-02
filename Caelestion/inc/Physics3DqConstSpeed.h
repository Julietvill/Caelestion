/*
 * Physics3D.h
 *
 *  Created on: Mar 1, 2018
 *      Author: wmagnus
 *
 */

#ifndef Physics3DqConstSpeed_H_
#define Physics3DqConstSpeed_H_

#include <Aspect.h>

class Physics3DqCS : Aspect
{
public:
	Physics3DqCS(Entity381 *ent);
	~Physics3DqCS();

	void Tick(float dt);
};



#endif /* Physics3DqConstSpeed_H_ */
