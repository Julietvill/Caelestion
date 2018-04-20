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
	friendlyCount = 0;
	enemyCount = 0;
}

EntityMgr::~EntityMgr(){

}

void EntityMgr::CreateEntityOfTypeAtPosition(EntityTypes entType, Ogre::Vector3 pos){

	Entity381 * ent;
	switch(entType){
	case friendlyTypeOne:
		ent = (Entity381 *) ( new friendlyOne(engine, pos, friendlyCount++));
		break;
	case friendlyTypeTwo:
		ent = (Entity381 *) (new friendlyTwo(engine, pos, friendlyCount++));
		break;
	case friendlyTypeThree:
		ent =  (Entity381 *) (new friendlyThree(engine, pos, friendlyCount++));
		break;
	case enemyTypeOne:
		ent = (Entity381 *) (new enemyOne(engine, pos, enemyCount++));
		break;
	case enemyTypeTwo:
		ent = (Entity381 *) (new enemyTwo(engine, pos, enemyCount++));
		break;
	case enemyTypeThree:
		ent = (Entity381 *) (new enemyThree(engine, pos, enemyCount++));
		break;
	default:
		ent = (Entity381*) (new friendlyOne(engine, pos, friendlyCount++));//CreateEntity("robot.mesh", pos);
		break;
	}
	ent->Init();
	if( ent->entityType == friendlyTypeOne ||ent->entityType == friendlyTypeTwo || ent->entityType == friendlyTypeThree)
	{
		friendlies.push_back(ent);
	}
	else
		enemies.push_back(ent);

}

void EntityMgr::Tick(float dt){
	for(unsigned int i = 0; i < friendlies.size(); i++){
		friendlies[i]->Tick(dt);
	}

	for(unsigned int index = 0; index < enemies.size(); index++){
		enemies[index]->Tick(dt);
	}
}
