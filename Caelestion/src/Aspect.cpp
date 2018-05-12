/*
 * Aspect.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <Aspect.h>
#include <Entity381.h>  //Aspect includes Entity381.h
#include <DebugDrawer.h>
#include <Engine.h>
#include <EntityMgr.h>
#include <GameMgr.h>
#include <UiMgr.h>
#include <MenuStates.h>
#include <Physics3DqConstSpeed.h>
#include <UnitAI.h>



Aspect::Aspect(Entity381 *ent){
	entity = ent;
}

Aspect::~Aspect(){

}

void Aspect::Tick(float dt){

}

//-------------------------------------------------------------------------------------------------------------------------------

Renderable::Renderable(Entity381* ent):Aspect(ent){

}

Renderable::~Renderable(){

}

void Renderable::Tick(float dt){
//do something;
	entity->sceneNode->setPosition(entity->position); //now ogre should render the sceneNode at the new position...
	entity->sceneNode->resetOrientation(); // yaw is cumulative, so set current y-rotation to 0
	entity->sceneNode->setOrientation(entity->actualFacing); //ogre's yaw is in the direction of -z
	//bounding boxes are rendered so...
	if(entity->isSelected)
		entity->sceneNode->showBoundingBox(true);
	else
		entity->sceneNode->showBoundingBox(false); //or we could do this in the entity mgr every time tab is pressed....
	//DebugDrawer::getSingleton().drawLine(entity->sceneNode->getPosition() + Ogre::Vector3(0,25,0), entity->sceneNode->getPosition() + (Ogre::Vector3(Ogre::Math::Cos(Ogre::Degree(entity->desiredHeading)), 0.25,Ogre::Math::Sin(Ogre::Degree(entity->desiredHeading))) * 100), Ogre::ColourValue::Blue);
}

//-------------------------------------------------------------------------------------------------------------------------------

healthStatus::healthStatus( Entity381* ent) : Aspect(ent){

}


healthStatus::~healthStatus(){

}

void healthStatus::resetStats(){
	entity->aspects.clear();
	//add all aspects that the entities will need to function
	Physics3DqCS* phx = new Physics3DqCS(entity);
	entity->aspects.push_back((Aspect*) phx);
	Renderable * renderable = new Renderable(entity);
	entity->aspects.push_back((Aspect*)renderable);
	UnitAI* ai = new UnitAI(entity);
	entity->aspects.push_back((Aspect*) ai);
	healthStatus* health = new healthStatus(entity);
	entity->aspects.push_back((Aspect*)health);
}

void healthStatus::Tick(float dt){

	if(entity->currentHealth <= 0){

		entity->position = entity->startPosition;
		entity->currentHealth = entity->maxHealth;

		resetStats();

		if( entity == entity->engine->entityMgr->caelestion || entity ==  entity->engine->entityMgr->yggdrasil)
		{
			entity->currentHealth = 0;
		}

		if(entity == entity->engine->entityMgr->playerEntity){
			entity->engine->uiMgr->prevState = entity->engine->uiMgr->uiState;
			Ogre::Degree z = Ogre::Degree(180.);
			entity->actualFacing.FromAngleAxis(z, Ogre::Vector3::UNIT_Y);
			entity->engine->uiMgr->uiState = respawState;

		}
	}

	if( (entity == entity->engine->entityMgr->yggdrasil) && !entity->engine->gameMgr->waveThreeUnlocked){
		entity->currentHealth = entity->maxHealth;
	}
}
