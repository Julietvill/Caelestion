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
	dest = Ogre::Vector3::ZERO;
}
MoveTo::~MoveTo(){

}

void MoveTo::Tick(float dt){
	//std::cout <<"IDENT" << myEnt->identity << std::endl;
	difference = dest - myEnt->position;
	//std::cout << difference << std::endl;
	difference = (myEnt->actualFacing.UnitInverse() * difference);
	//std::cout <<difference<<std::endl;
	//std::cout << dest << std::endl;
	double dyaw = atan2(difference.x, -difference.z) * 180/PI;

	double dpitch = atan2(difference.y, difference.z) * 180/PI;

	//std::cout << dyaw << std::endl;

	myEnt->desiredRotation = Ogre::Vector3(-dpitch,dyaw,0);
	//atan2(difference.y, sqrt(difference.z*difference.z + difference.x*difference.x)) * 180/PI
	//atan2(difference.z, difference.x) * 180/PI
}

//-------------------------------------------------------------------------------------------------------------------------------
Attack::Attack(Entity381* Ent, Entity381* target) : MoveTo(Ent){
	enemyTarget = target;

}

Attack::~Attack(){

}

void Attack::Tick(float dt){

}

//-------------------------------------------------------------------------------------------------------------------------------
Avoid::Avoid(Entity381* Ent, Entity381* target) : MoveTo(Ent){
	friendlyTarget = target;
	distSqr = 2500;
}

Avoid::~Avoid(){

}

void Avoid::Tick(float dt){
	myEnt->desiredRotation = Ogre::Vector3(45,0,0);
	distSqr = myEnt->position.squaredDistance(friendlyTarget->position);

	if( distSqr > thresholdSqr){
		//cout << "Complete" << endl;
		isComplete = true;
	}
}
