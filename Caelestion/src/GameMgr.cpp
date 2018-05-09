/*
 * GameMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <Engine.h>

#include <EntityMgr.h>
#include <GameMgr.h>
#include <GfxMgr.h>

#include <iostream>
#include <Types381.h>

#include <OgreOverlay.h>
#include <OgreSceneNode.h>

//Has no tick. Unaffected by pausing as a result.


GameMgr::GameMgr(Engine *engine): Mgr(engine), points(200)
{
	this->waveOneUnlocked = false;
	this->waveTwoUnlocked = false;
	this->waveThreeUnlocked = false;

}

GameMgr::~GameMgr() {
}

void GameMgr::Init(){
	  engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	  engine->gfxMgr->mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	  Ogre::Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
	  light->setPosition(20.0, 80.0, 50.0);

	  engine->gfxMgr->MakeSky();
	  Ogre::Vector3 startPos = engine->entityMgr->caelestionPos + Ogre::Vector3(0,0,50);
	  engine->entityMgr->CreateEntityOfTypeAtPosition(friendlyTypeOne,startPos);
	  engine->entityMgr->playerEntity = engine->entityMgr->entities[0];
	  engine->entityMgr->playerEntity->Lobotomize();
	  engine->entityMgr->playerEntity->currentHealth = 1;

	  engine->entityMgr->CreateEntityOfTypeAtPosition(enemyStation,engine->entityMgr->yggdrasilPos);
	  engine->entityMgr->yggdrasil = engine->entityMgr->entities[1];
	  engine->entityMgr->entities[1]->sceneNode->setScale(100,100,100);

	  engine->entityMgr->CreateEntityOfTypeAtPosition(friendlyStation,engine->entityMgr->caelestionPos);
	  engine->entityMgr->caelestion = engine->entityMgr->entities[2];
	  engine->entityMgr->entities[2]->sceneNode->setScale(100,100,100);

	  // a fixed point in the ocean so you can see relative motion
	  Ogre::Entity* ogreEntityFixed = engine->gfxMgr->mSceneMgr->createEntity("Asteroid_1.mesh");
	  Ogre::SceneNode* sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 0, 0));
	  sceneNode->attachObject(ogreEntityFixed);
	  sceneNode->showBoundingBox(true);
	  sceneNode->setScale(25,25,25);

	  //MakeEntities(friendlyTypeOne, enemyTypeOne, 25);
}

void GameMgr::LoadLevel(){

}

void GameMgr::Tick(float dt){
	if( !waveOneUnlocked && points >= 200){
		waveOneUnlocked = true;
		MakeEntities(friendlyTypeOne, enemyTypeOne, 25);
	}
	if( !waveTwoUnlocked && points >= 300){
		waveTwoUnlocked = true;
		MakeEntities(friendlyTypeTwo, enemyTypeTwo, 10);
	}
	if( !waveThreeUnlocked && points >= 400){
		waveThreeUnlocked = true;
		MakeEntities(friendlyTypeThree, enemyTypeThree, 5);
	}

	if( points <= 0 ){
		//game is over
		//engine->keepRunning = false;
	}

}

void GameMgr::MakeEntities(EntityTypes friendlyType, EntityTypes enemyType, int amount){

	//change the position, it can now be the same
	Ogre::Vector3 position = engine->entityMgr->yggdrasilPos;

	for( int i = 0; i < amount; i++){
		  engine->entityMgr->CreateEntityOfTypeAtPosition(enemyType,position);
		  position.x += 0.5;
	}

	position = engine->entityMgr->caelestionPos;
	for( int i = 0; i < amount; i++){
		  engine->entityMgr->CreateEntityOfTypeAtPosition(friendlyType,position);
		  position.x += 0.5;
	}

}

