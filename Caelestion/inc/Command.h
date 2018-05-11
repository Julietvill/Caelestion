/*
 * Command.h
 *
 *  Created on: Mar 28, 2018
 *      Author: julietv
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_

#include <Engine.h>
#include <OgreVector3.h>

class Entity381;
class UnitAI;

class Command {
public:
	Command();
	virtual ~Command();
	virtual void Tick(float dt);

	bool isComplete;
};
//-------------------------------------------------------------------------------------------------------------------------------

class MoveTo: public Command{
public:
	MoveTo(Entity381* ent);
	virtual ~MoveTo();
	virtual void Tick(float dt);

	Entity381* myEnt;
	float thresholdSqr;
	Ogre::Vector3 difference;
	Ogre::Vector3 dest;

};

//-------------------------------------------------------------------------------------------------------------------------------

class Attack : public MoveTo{
public:
	Attack(Entity381* Ent, Entity381* target);
	~Attack();
	void Tick(float dt);

	float attackTimer;
	const static float attackTime = 0.5f;


	Entity381* enemyTarget;
};

class Avoid : public MoveTo{
public:
	Avoid(Entity381* Ent, Entity381* entTarget);
	~Avoid();
	void Tick(float dt);

	Entity381* target;
	float distSqr;
};


#endif /* INC_COMMAND_H_ */
