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
	myEnt = Ent;

	difference = Ogre::Vector3::ZERO;
	thresholdSqr = 2500;
}
MoveTo::~MoveTo(){

}

void MoveTo::Tick(float dt){

}

//-------------------------------------------------------------------------------------------------------------------------------
Follow::Follow(Entity381* myEnt,Entity381* dest)
	: MoveTo(myEnt)
{
	targetEnt = dest;
	thresholdSqr = 1000000;
}

Follow::~Follow(){

}
void Follow::Tick(float dt){

}

//-------------------------------------------------------------------------------------------------------------------------------
Intercept::Intercept(Entity381* myEnt,Entity381* dest)
	: MoveTo(myEnt)
{
	targetEnt = dest;
	relVel = Ogre::Vector3::ZERO;
	relTime = 0;
	thresholdSqr = 2500;
}

Intercept::~Intercept(){

}
void Intercept::Tick(float dt){

}

//-------------------------------------------------------------------------------------------------------------------------------
Attack::Attack(){

}

Attack::~Attack(){

}

void Attack::Tick(float dt){

}
