/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <EntityMgr.h>
#include <Engine.h>

EntityMgr::EntityMgr(Engine *eng): Mgr(eng){
	playerEntity = 0;
	entCount = 0;
}

EntityMgr::~EntityMgr(){

}

void EntityMgr::CreateEntityOfTypeAtPosition(EntityTypes entType, Ogre::Vector3 pos){

	Entity381 * ent;
	switch(entType){
	case friendlyTypeOne:
		ent = new friendlyOne(engine, pos, entCount++);
		break;
	case friendlyTypeTwo:
		ent = new friendlyTwo(engine, pos, entCount++);
		break;
	case friendlyTypeThree:
		ent =  new friendlyThree(engine, pos, entCount++);
		break;
	case enemyTypeOne:
		ent = new enemyOne(engine, pos, entCount++);
		break;
	case enemyTypeTwo:
		ent = new enemyTwo(engine, pos, entCount++);
		break;
	case enemyTypeThree:
		ent = new enemyThree(engine, pos, entCount++);
		break;
	case friendlyStation:
		ent = new caelestionStation(engine, pos, entCount++);
		break;
	case Yggdrasil:

		break;
	default:
		ent = new friendlyOne(engine, pos, entCount++);//CreateEntity("robot.mesh", pos);
		break;
	}
	ent->Init();

	entities.push_back(ent);

}

void EntityMgr::Tick(float dt){
	// Don't simulate during pausetime.

	if(engine->paused == false)
	{
		for(unsigned int i = 0; i < entities.size(); i++){
			entities[i]->Tick(dt);
		}
	}

}
