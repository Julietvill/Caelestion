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

class Follow : public MoveTo{
public:
	Follow(Entity381* myEnt,Entity381* targetEnt);
	virtual ~Follow();
	void Tick(float dt);

	Entity381* targetEnt;
};
//-------------------------------------------------------------------------------------------------------------------------------

class Intercept : public MoveTo{
public:
	Intercept(Entity381* myEnt,Entity381* targetEnt);
	virtual ~Intercept();
	void Tick(float dt);

	Entity381* targetEnt;
	Ogre::Vector3 relVel;
	float relTime;

};
//-------------------------------------------------------------------------------------------------------------------------------

class Attack : public Command{
public:
	Attack();
	~Attack();
	void Tick(float dt);
	//will need a target
};


#endif /* INC_COMMAND_H_ */
