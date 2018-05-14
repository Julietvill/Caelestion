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
#include <EntityMgr.h>
#include <cstdlib>

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
	this->deathAudioID = 1;
	this->fireAudioID = 2;
	this->deathSound = "explosion.wav";
	this->fireSound = "Laser_light.wav"; //TODO: Replace this sound
	this->fireDone = false;
	this->deathDone = false;


	this->currentHealth = this->maxHealth = 100;				//we can change this based on how much health we want each entity to have
	this->hit = false;						//determines if the entity was hit or not.
	this->enemy = false;					//determines if the entity is an emeny or friendly, helps with attacking and avoidance.
	this->killMe = false;					//determines if the e381 needs purging
	this->attacking = false;				//determines if the entity is already attacking something so it doesn't add another entity to attack
	this->avoiding = false;

	this->owner = NULL;
	this->count = 20000;
	this->age = 0.f;
}

Entity381::~Entity381(){

}

void Entity381::Init(){
	name = meshfilename + IntToString(identity);
	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(name, meshfilename);
	if(matname != "") ogreEntity->setMaterialName(matname);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	sceneNode->attachObject(ogreEntity);

	if(entityType == projectileGeneric)
	{
		sceneNode->setScale(0.005, 0.005, 0.05);
		this->Lobotomize();
	}

	if(entityType == asteroidDefault )
	{
		int num = (rand() % 25) + 1;
		sceneNode->setScale(10.0/num,10.0/num,10.0/num);
	}

	if(entityType == enemyTypeTwo)
	{
		sceneNode->setScale(5,5,5);
	}

}


void Entity381::Tick(float dt){
	for(unsigned int i = 0; i < aspects.size(); i++){
		aspects[i]->Tick(dt);
	}
	age += dt;
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

	//weapons.push_back(new T1Projectile(Ogre::Vector3(0,0,0), this));

	for (unsigned int i = 0; i < weapons.size(); i++)
	{
		aspects.push_back(weapons[i]);
	}
}


void Entity381::switchPlayerEnt( EntityTypes type){

	this->Lobotomize();
	Ogre::Vector3 position = engine->entityMgr->caelestionPos + Ogre::Vector3(0,0,50);
	Ogre::Degree z = Ogre::Degree(180.);
	this->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);
	this->Lobotomize();

	this->sceneNode->detachObject(this->name);
	delete ogreEntity;
	ogreEntity = NULL;

	this->weapons.clear();

	Ogre::Entity* newTypeOfEntity = NULL;

	switch(type){
	case friendlyTypeOne:
		this->name =  meshfilename + IntToString(count);
		count++;
		newTypeOfEntity = engine->gfxMgr->mSceneMgr->createEntity(name,"Hastatus.mesh");
		if(matname != "") newTypeOfEntity->setMaterialName("Hastatus");

		this->velocity = Ogre::Vector3(0,0,50);

		this->speed = 50.0f;
		this->turnRate = 50.0f;
		this->climbRate = 1;
		this->currentHealth = this->maxHealth = 100;

		this->weapons.push_back((Weapon*) new T1Projectile(Ogre::Vector3(0,0,0), this));
//		this->weapons.push_back((Weapon*) new TestMcHuge(Ogre::Vector3(0,0,0), this));

		for (unsigned int i = 0; i < weapons.size(); i++)
		{
			aspects.push_back(weapons[i]);
		}

		engine->gfxMgr->cameraNode->setPosition(0, 3, 20);

		break;
	case friendlyTypeTwo:
		this->name =  meshfilename + IntToString(count);
		count++;
		newTypeOfEntity = engine->gfxMgr->mSceneMgr->createEntity(name,"gladius.mesh");
		if(matname != "") newTypeOfEntity->setMaterialName("Gladius");

		this->velocity = Ogre::Vector3(0,0,30);

		this->speed = 30.0f;
		this->turnRate = 30.0f;
		this->climbRate = 1;
		this->currentHealth = this->maxHealth = 200;

		this->weapons.push_back((Weapon*) new T2Projectile(Ogre::Vector3(0,0,0), this));
		for (unsigned int i = 0; i < weapons.size(); i++)
		{
			aspects.push_back(weapons[i]);
		}

		engine->gfxMgr->cameraNode->setPosition(0, 3, 20);
		break;
	case friendlyTypeThree:
		this->name =  meshfilename + IntToString(count);
		count++;
		newTypeOfEntity = engine->gfxMgr->mSceneMgr->createEntity(name,"Centurion.mesh");
		if(matname != "") newTypeOfEntity->setMaterialName("Centurion");

		this->velocity = Ogre::Vector3(0,0,0.1);
		this->speed = 15.0f;
		this->turnRate = 40.0f;
		this->climbRate = 1;
		this->currentHealth = this->maxHealth = 400;

		this->weapons.push_back((Weapon*) new T3Projectile(Ogre::Vector3(0,0,0), this));
		for (unsigned int i = 0; i < weapons.size(); i++)
		{
			aspects.push_back(weapons[i]);
		}

		engine->gfxMgr->cameraNode->setPosition(0, 7, 40);

		break;
	default:
		newTypeOfEntity = engine->gfxMgr->mSceneMgr->createEntity(name,"Hastatus.mesh");
		if(matname != "") newTypeOfEntity->setMaterialName("Hastatus");
		break;
	}

	this->sceneNode->attachObject(newTypeOfEntity);
	this->sceneNode->setPosition(position);
}

//-------------------------------------------------------------------------------------------------------------------------------

friendlyOne::friendlyOne(Engine *engine, Ogre::Vector3 pos, int identity):
		Entity381(engine, pos, identity){
	meshfilename = "Hastatus.mesh";
	matname = "Hastatus";
	entityType = friendlyTypeOne;

	//these values will need to be changed

	Ogre::Degree z = Ogre::Degree(180.);
	this->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);
	this->velocity = Ogre::Vector3(0,0,50);

	this->speed = 50.0f;
	this->turnRate = 50.0f;
	this->climbRate = 1;
	this->currentHealth = this->maxHealth = 100;

	enemy = false;

	//for friendlies this will be the number of points that you lose if you kill them.
	this->pointValue = -100;

	this->weapons.push_back((Weapon*) new T1Projectile(Ogre::Vector3(0,0,0), this));
	this->fireSound = "Assets/SFX/Laser_light.wav";

	for (unsigned int i = 0; i < weapons.size(); i++)
		{
			aspects.push_back(weapons[i]);
		}

}

friendlyOne::~friendlyOne(){

}
//-------------------------------------------------------------------------------------------------------------------------------

friendlyTwo::friendlyTwo(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "gladius.mesh";
	matname = "Gladius";
	entityType = friendlyTypeTwo;

	Ogre::Degree z = Ogre::Degree(180.);
	this->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);

	this->velocity = Ogre::Vector3(0,0,30);


	//these values will need to be changed
	this->speed = 30.0f;
	this->turnRate = 30.0f;
	this->climbRate = 1;
	this->currentHealth = this->maxHealth = 200;

	enemy = false;
	//for friendlies this will be the number of points that you lose if you kill them.
	this->pointValue = -250;

	this->weapons.push_back((Weapon*) new T2Projectile(Ogre::Vector3(0,0,0), this));
	for (unsigned int i = 0; i < weapons.size(); i++)
		{
			aspects.push_back(weapons[i]);
		}

}

friendlyTwo::~friendlyTwo(){

}
//-------------------------------------------------------------------------------------------------------------------------------

friendlyThree::friendlyThree(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "Centurion.mesh";
	matname = "Centurion";
	entityType = friendlyTypeThree;

	Ogre::Degree z = Ogre::Degree(180.);
	this->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);

	this->velocity = Ogre::Vector3(0,0,20);
	this->speed = 15.0f;
	this->turnRate = 40.0f;
	this->climbRate = 1;
	this->currentHealth = this->maxHealth = 400;

	enemy = false;

	//for friendlies this will be the number of points that you lose if you kill them.
	this->pointValue = -1000;

	this->weapons.push_back((Weapon*) new T3Projectile(Ogre::Vector3(0,0,0), this));
	for (unsigned int i = 0; i < weapons.size(); i++)
		{
			aspects.push_back(weapons[i]);
		}

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

	this->currentHealth = this->maxHealth = 250000;

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
	this->weapons.push_back((Weapon*) new T1Projectile(Ogre::Vector3(0,0,0), this));
	this->fireSound = "Assets/SFX/Laser_light.wav";
	this->pointValue = 25;

	for (unsigned int i = 0; i < weapons.size(); i++)
		{
			aspects.push_back(weapons[i]);
		}
}

enemyOne::~enemyOne(){

}
//-------------------------------------------------------------------------------------------------------------------------------

enemyTwo::enemyTwo(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "Jotnar.mesh";
	matname = "Jotnar/SOLID/TEX/Jotnar.png";
	entityType = enemyTypeTwo;

	this->velocity = Ogre::Vector3(0,0,-15);


	Ogre::Degree z = Ogre::Degree(180.);
	this->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);

	this->currentHealth = this->maxHealth = 200;

	//these values will need to be changed
	this->speed = 15.0f;
	this->turnRate = 50.0f;
	this->climbRate = 1;
	enemy = true;

	//for enemies this will be the number of points that you gain when you kill them.
	this->pointValue = 50;
	this->weapons.push_back((Weapon*) new T2Projectile(Ogre::Vector3(0,0,0), this));
	for (unsigned int i = 0; i < weapons.size(); i++)
		{
			aspects.push_back(weapons[i]);
		}

}

enemyTwo::~enemyTwo(){

}
//-------------------------------------------------------------------------------------------------------------------------------

enemyThree::enemyThree(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "Valkyrie.mesh";
	matname = "Valkyrie";
	entityType = enemyTypeThree;

	this->velocity = Ogre::Vector3(0,0,-20);

	Ogre::Degree z = Ogre::Degree(180.);
	this->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);

	this->currentHealth = this->maxHealth = 400;


	//these values will need to be changed
	this->speed = 15.0f;
	this->turnRate = 10.0f;
	this->climbRate = 1;
	enemy = false;
	//for enemies this will be the number of points that you gain when you kill them.
	this->pointValue = 75;
	this->weapons.push_back((Weapon*) new T3Projectile(Ogre::Vector3(0,0,0), this));
	for (unsigned int i = 0; i < weapons.size(); i++)
		{
			aspects.push_back(weapons[i]);
		}

}

enemyThree::~enemyThree(){

}

//-------------------------------------------------------------------------------------------------------------------------------

Yggdrasil::Yggdrasil(Engine *engine, Ogre::Vector3 pos, int identity):
				Entity381(engine, pos, identity){
	meshfilename = "Yggdrasill.mesh";
	matname = "Yggdrasill";
	entityType = enemyStation;

	this->velocity = Ogre::Vector3(0,0,0);

	Ogre::Degree z = Ogre::Degree(180.);
	this->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);

	this->currentHealth = this->maxHealth = 250000;

	this->speed = 0.f;
	this->turnRate = 0.f;
	this->climbRate = 0;

	enemy = true;
}

Yggdrasil::~Yggdrasil(){

}

Asteroid::Asteroid(Engine *engine, Ogre::Vector3 pos, int identity):
	Entity381(engine, pos, identity)
{
	//TODO: Randomize Asteroids
	int num = (rand() % 2) + 1;
	std::string f_name = "Asteroid_" + IntToString(num);
	meshfilename = f_name + ".mesh";
	matname = f_name;
	entityType = asteroidDefault;

	Ogre::Degree z = Ogre::Degree(180.);

	this->velocity = Ogre::Vector3(0,0,0);
	this->speed = 0.f;
	this->turnRate = 0.f;
	this->climbRate = 0;
	this->currentHealth = this->maxHealth = 2500000;
	this->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);

	enemy = false;
}

Asteroid::~Asteroid(){}

//--------------------------------------------------------------------------------------------------------------------------
Projectile::Projectile(Engine* engine, Ogre::Vector3 pos, int identity, Weapon* owner):
		Entity381(engine,pos,identity)
{
	meshfilename = "cube.mesh";

	entityType = projectileGeneric;

	float osp = owner->entity->velocity.length();

	if(owner != NULL && owner->entity != NULL)
	{
		this->velocity =  Ogre::Vector3(0,0,-500-osp);
		this->actualFacing = owner->entity->actualFacing;
	}
	else
	{
		this->velocity = Ogre::Vector3(0,0,0);
		this->actualFacing = Ogre::Quaternion::IDENTITY;
	}

	this->currentHealth = this->maxHealth = 5;

	this->speed = 0.f;
	this->turnRate = 0.f;
	this->climbRate = 0;

	enemy = false;

	this->owner= owner;

	this->agelim = 5.f;
}

Projectile::~Projectile(){}

void Projectile::Tick(float dt)
{
	for(unsigned int i = 0; i < aspects.size(); i++){
		aspects[i]->Tick(dt);
	}
	age += dt;

	if(age > agelim) killMe = true;
}
