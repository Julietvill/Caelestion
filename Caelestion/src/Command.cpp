/*
 * Command.cpp
 *
 *  Created on: Mar 28, 2018
 *      Author: julietv
 */

#include <Command.h>
#include <Entity381.h>
#include <Utils.h>
#include <math.h>
#include <UnitAI.h>

using namespace std;

#define PI 3.14156265

Command::Command(){
	isComplete = false;
}
Command::~Command(){

}
void Command::Tick(float dt){

}

//-------------------------------------------------------------------------------------------------------------------------------
MoveTo::MoveTo(Entity381* Ent){
	this->myEnt = Ent;

	this->difference = Ogre::Vector3::ZERO;
	this->thresholdSqr = 2500;
	this->dest = Ogre::Vector3::ZERO;
}
MoveTo::~MoveTo(){

}

void MoveTo::Tick(float dt){
	difference = dest - myEnt->position;
	difference = (myEnt->actualFacing.UnitInverse() * difference);

	double dyaw = atan2(difference.x, -difference.z) * 180/PI;
	double dpitch = atan2(difference.y, difference.z) * 180/PI;

	myEnt->desiredRotation = Ogre::Vector3(-dpitch,dyaw,0);
}

//-------------------------------------------------------------------------------------------------------------------------------
Attack::Attack(Entity381* Ent, Entity381* target): MoveTo(Ent){
	this->enemyTarget = target;
	this->attackTimer = this->attackTime;
	myEnt->attacking = true;

}

Attack::~Attack(){

}

void Attack::Tick(float dt){
	attackTimer -= dt;
	difference = enemyTarget->position - myEnt->position;
	difference = (myEnt->actualFacing.UnitInverse() * difference);

	double dyaw = atan2(difference.x, -difference.z) * 180/PI;
	double dpitch = atan2(difference.y, difference.z) * 180/PI;

	myEnt->desiredRotation = Ogre::Vector3(-dpitch,dyaw,0);

	//need to add a dimention of time
	if( !myEnt->weapons.empty() && attackTimer < 0){
		myEnt->weapons[0]->Fire(dt);
		attackTimer = attackTime;
	}
	if( enemyTarget->currentHealth == 0){
		isComplete = true;
		myEnt->attacking = false;
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
Avoid::Avoid(Entity381* Ent, Entity381* target) : MoveTo(Ent){
	this->target = target;
	this->distSqr = 2500;
	myEnt->avoiding = true;
}

Avoid::~Avoid(){

}

void Avoid::Tick(float dt){

	difference = myEnt->position - target->position;
	difference = (myEnt->actualFacing.UnitInverse() * difference);

	double dyaw = atan2(difference.x, -difference.z) * 90/PI;
	double dpitch = atan2(difference.y, difference.z) * 90/PI;

	myEnt->desiredRotation = Ogre::Vector3(-dpitch,dyaw,0);

	distSqr = myEnt->position.squaredDistance(target->position);

	if( distSqr > thresholdSqr){
		isComplete = true;
		myEnt->avoiding = false;
	}
}
