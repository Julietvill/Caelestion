/*
 * Physics3D.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: sushil
 */


#include <Entity381.h>
#include <Physics3D.h>
#include <Utils.h>

using namespace std;

Physics3D::Physics3D(Entity381* ent):Aspect(ent){

}

Physics3D::~Physics3D(){

}


void Physics3D::Tick(float dt){

	entity->heading = Ogre::Math::lerp(entity->heading, entity->desiredHeading, entity->turnRate * dt);
	entity->altitude = Ogre::Math::lerp(entity->altitude, entity->desiredAltitude, entity->climbRate * dt);


	//Now do the trig
	entity->velocity.y = 0.0f; // just to be safe, we do not want ships in the air.
	entity->velocity.x = Ogre::Math::Sin(Ogre::Degree(entity->heading)) * entity->speed;
	entity->velocity.z = Ogre::Math::Cos(Ogre::Degree(entity->heading)) * entity->speed * -1;


	entity->position = entity->position + entity->velocity * dt;
}
