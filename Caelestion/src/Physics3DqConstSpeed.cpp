/*
 * Physics3DqCS.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: wmagnus
 */

#ifndef Physics3DqConstSpeed_C_
#define Physics3DqConstSpeed_C_

#include <Entity381.h>
#include <Engine.h>
#include <EntityMgr.h>
#include <GameMgr.h>
#include <Physics3DqConstSpeed.h>
#include <Utils.h>

using namespace std;

Physics3DqCS::Physics3DqCS(Entity381* ent):Aspect(ent){

}

Physics3DqCS::~Physics3DqCS(){

}


void Physics3DqCS::Tick(float dt){


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

	entity->velocity = -1* entity->velocity.length() * entity->actualFacing.zAxis();


	if(entity->acc >= 1)
	{
		//dv.x = dt * entity->speed * entity->actualFacing.xAxis();
		//dv.y = dt * entity->speed * entity->actualFacing.yAxis();
		dv = -dt * entity->speed * entity->actualFacing.zAxis();
	}
	if(entity->acc <= -1)
	{
		if (entity->velocity.length() < dt*entity->speed)
		{
			entity->velocity = Ogre::Vector3::ZERO;
			dv = Ogre::Vector3::ZERO;
		}
		else
		{
			dv = dt * entity->speed * entity->actualFacing.zAxis();
		}
	}


	//dv otherwise remains zero, no slowing down for the weak

	entity->velocity = entity->velocity + dv;

	entity->position = entity->position + entity->velocity*dt;

	//And now, collision.

	//Projectile Weapons case only.
	bool intersect = false;
	for(unsigned int i = 0; i < entity->engine->entityMgr->projectiles.size(); i++)
	{
		if(entity != entity->engine->entityMgr->projectiles[i])
		{
			if(entity->engine->entityMgr->projectiles[i]->owner != NULL && entity->engine->entityMgr->projectiles[i]->owner->entity != entity)
			{
				intersect = (entity->sceneNode->_getWorldAABB().intersects(entity->engine->entityMgr->projectiles[i]->sceneNode->_getWorldAABB()));
			}
		}
		if(intersect)
		{
			std::cout << "INTERSECT AT " << entity->identity << ": " << entity->engine->entityMgr->projectiles[i]->position << std:: endl;
			entity->engine->entityMgr->projectiles[i]->killMe = true;
			entity->currentHealth -= entity->engine->entityMgr->projectiles[i]->owner->dmgOnHit;

			if(entity->currentHealth <= 0 && entity->engine->entityMgr->projectiles[i]->owner->entity == entity->engine->entityMgr->playerEntity)
			{
				entity->engine->gameMgr->points += entity->pointValue;
			}
		}
		intersect = false;
	}
}

#endif /* Physics3DqConstSpeed_C_ */
