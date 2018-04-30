/*
 * Entity381.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <GfxMgr.h>

#include<Entity381.h>
#include <Physics3D.h>
#include <Physics3Dq.h>
#include <UnitAI.h>

std::string IntToString(int x){
	char tmp[10000];
	sprintf(tmp, "%i", x);
	return std::string(tmp);
}

Entity381::Entity381(Engine *engine, Ogre::Vector3 pos, int ident){

	this->engine = engine;

	entityType = defaultEnt;
	meshfilename = std::string();
	matname = "";
	position = pos;
	velocity = Ogre::Vector3(0, 0, 0);
	actualFacing = Ogre::Quaternion(1,0,0,1);

	identity = ident;
	isSelected = false;

	name = "Entity381";
	sceneNode = 0;
	ogreEntity = 0;

	Physics3Dq* phx = new Physics3Dq(this);
	aspects.push_back((Aspect*) phx);
	Renderable * renderable = new Renderable(this);
	aspects.push_back((Aspect*)renderable);
	UnitAI* ai = new UnitAI(this);
	aspects.push_back((Aspect*) ai);

	this->desiredHeading = this->heading = 0;
	this->turnRate = 0;
	this->speed = 0; //this represents delta speed now, by edict of wmagnus
	this->acc = 0;

	this->minAltitude = 0;
	this->maxAltitude = 1000;
	this->altitude = 0;
	this->desiredAltitude = 0;
	this->climbRate = 1;

	this->pointValue = 0;
	this->desiredRotation = Ogre::Vector3::ZERO; //ZERO ROTATION DESIRED.
	//this->desiredRotation = Ogre::Vector3(25, 50, 75);

	//sound
	this->playSound = false;
	this->auioID = 0;
	this->soundFile = "Boat-Sound.wav";		//this will need to be changed **NEEDS UPDATE**
	this->didSelectSoundPlay = false;

}

Entity381::~Entity381(){

}

void Entity381::Init(){
	name = meshfilename + IntToString(identity);
	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshfilename);
	if(matname != "") ogreEntity->setMaterialName(matname);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	sceneNode->attachObject(ogreEntity);
}

void Entity381::Tick(float dt){
	for(unsigned int i = 0; i < aspects.size(); i++){
		aspects[i]->Tick(dt);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------

friendlyOne::friendlyOne(Engine *engine, Ogre::Vector3 pos, int identity):
		Entity381(engine, pos, identity){
	meshfilename = "Hastatus.mesh";
	matname = "Hastatus/Texture";
	entityType = friendlyTypeOne;

	//these values will need to be changed
	this->velocity = Ogre::Vector3(0,0,-0.1);

	this->speed = 50.0f;
	this->turnRate = 50.f;
	this->climbRate = 1;

	//for friendlies this will be the number of points that you lose if you kill them.
	this->pointValue = 10;
}

friendlyOne::~friendlyOne(){

}
//-------------------------------------------------------------------------------------------------------------------------------

friendlyTwo::friendlyTwo(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "Gladius.mesh";
	matname = "Gladius/Texture";
	entityType = friendlyTypeTwo;

	//these values will need to be changed
	this->speed = 15.0f;
	this->turnRate = 10.0f;
	this->climbRate = 1;

	//for friendlies this will be the number of points that you lose if you kill them.
	this->pointValue = 10;
}

friendlyTwo::~friendlyTwo(){

}
//-------------------------------------------------------------------------------------------------------------------------------

friendlyThree::friendlyThree(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "cube.mesh";
	entityType = friendlyTypeThree;

	//these values will need to be changed
	this->speed = 15.0f;
	this->turnRate = 10.0f;
	this->climbRate = 1;

	//for friendlies this will be the number of points that you lose if you kill them.
	this->pointValue = 10;
}

friendlyThree::~friendlyThree(){

}
//-------------------------------------------------------------------------------------------------------------------------------

enemyOne::enemyOne(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "sphere.mesh";
	entityType = enemyTypeOne;

	//these values will need to be changed
	this->speed = 15.0f;
	this->turnRate = 10.0f;
	this->climbRate = 1;

	//for enemies this will be the number of points that you gain when you kill them.
	this->pointValue = 25;
}

enemyOne::~enemyOne(){

}
//-------------------------------------------------------------------------------------------------------------------------------

enemyTwo::enemyTwo(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "sphere.mesh";
	entityType = enemyTypeTwo;

	//these values will need to be changed
	this->speed = 15.0f;
	this->turnRate = 10.0f;
	this->climbRate = 1;

	//for enemies this will be the number of points that you gain when you kill them.
	this->pointValue = 50;
}

enemyTwo::~enemyTwo(){

}
//-------------------------------------------------------------------------------------------------------------------------------

enemyThree::enemyThree(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "sphere.mesh";
	entityType = enemyTypeThree;

	//these values will need to be changed
	this->speed = 15.0f;
	this->turnRate = 10.0f;
	this->climbRate = 1;

	//for enemies this will be the number of points that you gain when you kill them.
	this->pointValue = 75;
}

enemyThree::~enemyThree(){

}
