/*
 * Physics3Dq.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: wmagnus
 */

#ifndef Physics3Dq_C_
#define Physics3Dq_C_

#include <Entity381.h>
#include <Physics3Dq.h>
#include <Utils.h>

using namespace std;

Physics3Dq::Physics3Dq(Entity381* ent):Aspect(ent){

}

Physics3Dq::~Physics3Dq(){

}


void Physics3Dq::Tick(float dt){


	//actualFacing is 3d facing for the object now.
	//desiredRotation is the amount of rotation currently demanded. <pitch, yaw, roll>

	//std::cout<<entity->desiredRotation<<std::endl;

	Ogre::Quaternion rotNow = Ogre::Quaternion::IDENTITY; //init

	Ogre::Vector3 dv = Ogre::Vector3::ZERO; // delta velocity

	Ogre::Vector3 ratioAdjustFacings = entity->desiredRotation.normalisedCopy();


	float tr = entity->desiredRotation.length(); // applied turnrate

	if (tr > entity->turnRate*dt)
	{
		tr = entity->turnRate*dt;
	}

	entity->desiredRotation = entity->desiredRotation - ratioAdjustFacings * tr;
	//if(entity->desiredRotation.length() < entity->turnRate*dt) entity->desiredRotation = Ogre::Vector3::ZERO;


	rotNow.FromAngleAxis(Ogre::Degree(tr), ratioAdjustFacings);
	rotNow.normalise();



	entity->actualFacing = entity->actualFacing * rotNow.Inverse();
	entity->actualFacing.normalise();
	//std::cout << entity->actualFacing << std::endl;

	//entity->actualFacing = Ogre::Quaternion(.5,0.,0.,.5);


	if(entity->acc >= 1)
	{
			//dv.x = dt * entity->speed * entity->actualFacing.xAxis();
			//dv.y = dt * entity->speed * entity->actualFacing.yAxis();
			dv = -dt * entity->speed * entity->actualFacing.zAxis();
	}
	//dv otherwise remains zero, no slowing down for the weak

	entity->velocity = entity->velocity + dv;

	entity->position = entity->position + entity->velocity*dt;

	/*
	entity->heading = Ogre::Math::lerp(entity->heading, entity->desiredHeading, entity->turnRate * dt);
	entity->altitude = Ogre::Math::lerp(entity->altitude, entity->desiredAltitude, entity->climbRate * dt);


	//Now do the trig
	entity->velocity.y = 0.0f; // just to be safe, we do not want ships in the air.
	entity->velocity.x = Ogre::Math::Sin(Ogre::Degree(entity->heading)) * entity->speed;
	entity->velocity.z = Ogre::Math::Cos(Ogre::Degree(entity->heading)) * entity->speed * -1;


	entity->position = entity->position + entity->velocity * dt;
	*/
}

#endif /* Physics3Dq_C_ */
