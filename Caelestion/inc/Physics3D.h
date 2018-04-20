/*
 * Physics3D.h
 *
 *  Created on: Mar 1, 2018
 *      Author: sushil
 */

#ifndef Physics3D_H_
#define Physics3D_H_

#include <Aspect.h>

class Physics3D : Aspect
{
public:
	Physics3D(Entity381 *ent);
	~Physics3D();

	void Tick(float dt);
};



#endif /* Physics3D_H_ */
