/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <EntityMgr.h>
#include <GfxMgr.h>
#include <Engine.h>

EntityMgr::EntityMgr(Engine *eng): Mgr(eng){
	playerEntity = 0;
	caelestion = 0;
	yggdrasil = 0;
	entCount = 0;

	yggdrasilPos = Ogre::Vector3(0,0,2500);
	caelestionPos = Ogre::Vector3(0,0,-2500);
}

EntityMgr::~EntityMgr(){

}

void EntityMgr::CreateProjectile(Ogre::Vector3 pos, Weapon* owner)
{
	Entity381* ent;
	ent = new Projectile(engine, pos, projCount++, owner);

	ent->Init();
	projectiles.push_back(ent);
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
	case enemyStation:
		ent = new Yggdrasil(engine, pos, entCount++);
		break;
	case projectileGeneric:
		ent = new Projectile(engine, pos, projCount++, NULL);
		break;
	default:
		ent = new friendlyOne(engine, pos, entCount++);//CreateEntity("robot.mesh", pos);
		break;
	}
	ent->Init();

	if(ent->identity < 1000) entities.push_back(ent);
	else projectiles.push_back(ent);

}

void EntityMgr::Tick(float dt){
	// Don't simulate during pausetime.

	Ogre::SceneNode* kill;
		if(engine->paused == false)
		{
			for(unsigned int i = 0; i < entities.size(); i++){
				entities[i]->Tick(dt);
			}

			for(unsigned int i = 0; i < projectiles.size(); i++)
			{
				projectiles[i]->Tick(dt);
			}

			for(unsigned int i = 0; i < projectiles.size(); i++)
			{
				kill = NULL;
				/*
				if(projectiles[i]->position.length() > 5000)
				{
					projectiles[i]->killMe = true;
				}
				*/

				if(projectiles[i]->killMe)
				{
					kill = projectiles[i]->sceneNode;
					engine->gfxMgr->mSceneMgr->destroySceneNode(kill);
					projectiles.erase(projectiles.begin()+i);
					i--;
					}
			}
			std::cout << "Projectiles Count: " << projectiles.size() << std::endl;

		}

}
