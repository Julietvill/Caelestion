/*
 * Entity381.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <GfxMgr.h>

#include<Entity381.h>
#include <Physics3D.h>
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
	position = pos;
	velocity = Ogre::Vector3(0, 0, 0);
	identity = ident;
	isSelected = false;

	name = "Entity381";
	sceneNode = 0;
	ogreEntity = 0;

	Physics3D* phx = new Physics3D(this);
	aspects.push_back((Aspect*) phx);
	Renderable * renderable = new Renderable(this);
	aspects.push_back((Aspect*)renderable);
	UnitAI* ai = new UnitAI(this);
	aspects.push_back((Aspect*) ai);

	this->desiredHeading = this->heading = 0;
	this->turnRate = 0;
	this->speed = 0;

	this->minAltitude = 0;
	this->maxAltitude = 1000;
	this->altitude = 0;
	this->desiredAltitude = 0;
	this->climbRate = 1;

	this->pointValue = 0;
}

Entity381::~Entity381(){

}

void Entity381::Init(){
	name = meshfilename + IntToString(identity);
	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshfilename);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	sceneNode->attachObject(ogreEntity);
}

void Entity381::Tick(float dt){
	for(unsigned int i = 0; i < aspects.size(); i++){
		aspects[i]->Tick(dt);
	}
}

void Entity381::moveTo(Ogre::Vector3 dest, bool AddToCommand){
	MoveTo* ai = new MoveTo(this);
	ai->dest = dest;

	if(AddToCommand)
		aspects[2]->AddCommand(ai);
	else
		aspects[2]->SetCommand(ai);

}
void Entity381::InterceptEnt(Entity381* dest, bool AddToCommand){
	Intercept* ai = new Intercept(this, dest);

	if(AddToCommand)
		aspects[2]->AddCommand(ai);
	else
		aspects[2]->SetCommand(ai);
}
void Entity381::FollowEnt(Entity381* dest, bool AddToCommand){
	Follow* ai = new Follow(this, dest);

	if(AddToCommand)
		aspects[2]->AddCommand(ai);
	else
		aspects[2]->SetCommand(ai);
}

//-------------------------------------------------------------------------------------------------------------------------------

friendlyOne::friendlyOne(Engine *engine, Ogre::Vector3 pos, int identity):
		Entity381(engine, pos, identity){
	meshfilename = "cube.mesh";
	entityType = friendlyTypeOne;

	//these values will need to be changed
	this->speed = 50.0f;
	this->turnRate = 5.0f;
	this->climbRate = 1;

	//for friendlies this will be the number of points that you lose if you kill them.
	this->pointValue = 10;
}

friendlyOne::~friendlyOne(){

}
//-------------------------------------------------------------------------------------------------------------------------------

friendlyTwo::friendlyTwo(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "cube.mesh";
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
	meshfilename = "circle.mesh";
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
	meshfilename = "circle.mesh";
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
	meshfilename = "circle.mesh";
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
