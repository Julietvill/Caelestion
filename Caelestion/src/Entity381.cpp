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
#include <Physics3DqConstSpeed.h>
#include <UnitAI.h>
#include <SoundMgr.h>

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
	startPosition = pos;
	velocity = Ogre::Vector3(0, 0, 0);
	actualFacing = Ogre::Quaternion(1,0,0,1);

	identity = ident;
	isSelected = false;

	name = "Entity381";
	sceneNode = 0;
	ogreEntity = 0;

	//enemyHQ = Ogre::Vector3::ZERO;

	//add all aspects that the entities will need to function
	Physics3DqCS* phx = new Physics3DqCS(this);
	aspects.push_back((Aspect*) phx);
	Renderable * renderable = new Renderable(this);
	aspects.push_back((Aspect*)renderable);
	UnitAI* ai = new UnitAI(this);
	aspects.push_back((Aspect*) ai);
	healthStatus* health = new healthStatus(this);
	aspects.push_back((Aspect*)health);

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

	this->currentHealth = this->maxHealth = 100;				//we can change this based on how much health we want each entity to have
	this->hit = false;						//determines if the entity was hit or not.
	this->enemy = false;					//determines if the entity is an emeny or friendly, helps with attacking and avoidance.

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

void Entity381::Lobotomize()
{
	aspects.clear(); //Erase all aspects

	//Restore aspects that aren't AI
	Physics3DqCS* phx = new Physics3DqCS(this);
	aspects.push_back((Aspect*) phx);
	Renderable * renderable = new Renderable(this);
	aspects.push_back((Aspect*)renderable);
	healthStatus* health = new healthStatus(this);
	aspects.push_back((Aspect*)health);
}

//-------------------------------------------------------------------------------------------------------------------------------

friendlyOne::friendlyOne(Engine *engine, Ogre::Vector3 pos, int identity):
		Entity381(engine, pos, identity){
	meshfilename = "Hastatus.mesh";
	matname = "Hastatus/Texture";
	entityType = friendlyTypeOne;

	//these values will need to be changed
	this->velocity = Ogre::Vector3(0,0,50);

	Ogre::Degree z = Ogre::Degree(180.);
	this->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);

	this->speed = 50.0f;
	this->turnRate = 50.0f;
	this->climbRate = 1;
	this->currentHealth = this->maxHealth = 100;

	enemy = false;

	//for friendlies this will be the number of points that you lose if you kill them.
	this->pointValue = -100;

	this->weapons.push_back((Weapon*) new T1Killray(Ogre::Vector3(0,0,0), this));
	this->soundFile = "Assets/SFX/Laser_light.wav";

}

friendlyOne::~friendlyOne(){

}
//-------------------------------------------------------------------------------------------------------------------------------

friendlyTwo::friendlyTwo(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "gladius.mesh";
	matname = "Gladius/Texture";
	entityType = friendlyTypeTwo;

	this->velocity = Ogre::Vector3(0,0,30);

	Ogre::Degree z = Ogre::Degree(180.);
	this->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);


	//these values will need to be changed
	this->speed = 30.0f;
	this->turnRate = 30.0f;
	this->climbRate = 1;
	this->currentHealth = this->maxHealth = 100;

	enemy = false;
	//for friendlies this will be the number of points that you lose if you kill them.
	this->pointValue = -250;
}

friendlyTwo::~friendlyTwo(){

}
//-------------------------------------------------------------------------------------------------------------------------------

friendlyThree::friendlyThree(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "cube.mesh";
	entityType = friendlyTypeThree;

	this->velocity = Ogre::Vector3(0,0,0.1);

	Ogre::Degree z = Ogre::Degree(180.);
	this->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);
	this->speed = 15.0f;
	this->turnRate = 40.0f;
	this->climbRate = 1;
	this->currentHealth = this->maxHealth = 100;

	enemy = false;

	//for friendlies this will be the number of points that you lose if you kill them.
	this->pointValue = -1000;
}

friendlyThree::~friendlyThree(){

}

//-------------------------------------------------------------------------------------------------------------------------------

caelestionStation::caelestionStation(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "Caelestion_station.mesh";
	matname = "Caelestion_Station";
	entityType = friendlyStation;

	this->velocity = Ogre::Vector3(0,0,0);

	Ogre::Degree z = Ogre::Degree(180.);
	this->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);

	this->currentHealth = this->maxHealth = 100;

	this->speed = 0.f;
	this->turnRate = 0.f;
	this->climbRate = 0;

	enemy = false;
}

caelestionStation::~caelestionStation(){

}
//-------------------------------------------------------------------------------------------------------------------------------

enemyOne::enemyOne(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "Aesir.mesh";
	matname = "Aesir/Texture";
	entityType = enemyTypeOne;

	this->velocity = Ogre::Vector3(0,0,-50);

	Ogre::Degree z = Ogre::Degree(180.);
	this->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);

	this->currentHealth = this->maxHealth = 100;

	this->speed = 50.0f;
	this->turnRate = 50.0f;
	this->climbRate = 1;

	enemy = true;

	//for enemies this will be the number of points that you gain when you kill them.
	this->weapons.push_back((Weapon*) new T1Killray(Ogre::Vector3(0,0,0), this));
	this->soundFile = "Assets/SFX/Laser_light.wav";
	this->pointValue = 25;
}

enemyOne::~enemyOne(){

}
//-------------------------------------------------------------------------------------------------------------------------------

enemyTwo::enemyTwo(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "cube.mesh";
	entityType = enemyTypeTwo;

	this->velocity = Ogre::Vector3(0,0,-15);


	Ogre::Degree z = Ogre::Degree(180.);
	this->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);

	this->currentHealth = this->maxHealth = 100;

	//these values will need to be changed
	this->speed = 15.0f;
	this->turnRate = 50.0f;
	this->climbRate = 1;
	enemy = true;

	//for enemies this will be the number of points that you gain when you kill them.
	this->pointValue = 50;
}

enemyTwo::~enemyTwo(){

}
//-------------------------------------------------------------------------------------------------------------------------------

enemyThree::enemyThree(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "cube.mesh";
	entityType = enemyTypeThree;

	this->velocity = Ogre::Vector3(0,0,-0.1);

	Ogre::Degree z = Ogre::Degree(180.);
	this->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);

	this->currentHealth = this->maxHealth = 100;


	//these values will need to be changed
	this->speed = 15.0f;
	this->turnRate = 10.0f;
	this->climbRate = 1;
	enemy = false;
	//for enemies this will be the number of points that you gain when you kill them.
	this->pointValue = 75;
}

enemyThree::~enemyThree(){

}

//-------------------------------------------------------------------------------------------------------------------------------

Yggdrasil::Yggdrasil(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "Caelestion_station.mesh";
	matname = "Caelestion_Station";
	entityType = enemyTypeOne;

	this->velocity = Ogre::Vector3(0,0,0);

	Ogre::Degree z = Ogre::Degree(180.);
	this->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);

	this->currentHealth = this->maxHealth = 100;

	this->speed = 0.f;
	this->turnRate = 0.f;
	this->climbRate = 0;

	enemy = true;
}

Yggdrasil::~Yggdrasil(){

}
