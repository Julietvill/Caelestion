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
#include <UiMgr.h>
#include <MenuStates.h>

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
	  this->CreateMainEntities();
}

void GameMgr::LoadLevel(){

}

void GameMgr::CreateMainEntities(){
	  //create the start ship
	  Ogre::Vector3 startPos = engine->entityMgr->caelestionPos + Ogre::Vector3(0,0,50);
	  engine->entityMgr->CreateEntityOfTypeAtPosition(friendlyTypeOne,startPos);
	  engine->entityMgr->playerEntity = engine->entityMgr->entities[0];
	  engine->entityMgr->playerEntity->Lobotomize();


	  engine->entityMgr->CreateEntityOfTypeAtPosition(enemyStation,engine->entityMgr->yggdrasilPos);
	  engine->entityMgr->yggdrasil = engine->entityMgr->entities[1];
	  engine->entityMgr->entities[1]->sceneNode->setScale(100,100,100);

	  engine->entityMgr->CreateEntityOfTypeAtPosition(friendlyStation,engine->entityMgr->caelestionPos);
	  engine->entityMgr->caelestion = engine->entityMgr->entities[2];
	  engine->entityMgr->entities[2]->sceneNode->setScale(100,100,100);

	  // a fixed point in the SPACE so you can see relative motion
      CreateAsteroidField();
	  //engine->entityMgr->playerEntity->currentHealth = -1;
}

void GameMgr::Tick(float dt){

	if( !waveOneUnlocked && points >= 0){
		waveOneUnlocked = true;
		MakeEntities(friendlyTypeOne, enemyTypeOne, 25);
	}
	if( !waveTwoUnlocked && points >= 300){
		waveTwoUnlocked = true;
		MakeEntities(friendlyTypeTwo, enemyTypeTwo, 10);
	}
	if( !waveThreeUnlocked && points >= 500){
		waveThreeUnlocked = true;
		MakeEntities(friendlyTypeThree, enemyTypeThree, 5);
	}

	if( points <= 0 || engine->entityMgr->caelestion->currentHealth <= 0){
		engine->uiMgr->uiState = gameLostState;
	}

	else if( engine->entityMgr->yggdrasil->currentHealth <= 0){
		engine->uiMgr->uiState = gameWinState;
	}

}

void GameMgr::restart(){
	engine->entityMgr->entities.clear();
	this->CreateMainEntities();
	this->waveOneUnlocked = false;
	this->waveTwoUnlocked = false;
	this->waveThreeUnlocked = false;

}

void GameMgr::MakeEntities(EntityTypes friendlyType, EntityTypes enemyType, int amount){

	//change the position, it can now be the same
	Ogre::Vector3 position = engine->entityMgr->yggdrasilPos;

	for( int i = 0; i < amount; i++){
		  engine->entityMgr->CreateEntityOfTypeAtPosition(enemyType,position);
	}

	position = engine->entityMgr->caelestionPos;
	for( int i = 0; i < amount; i++){
		  engine->entityMgr->CreateEntityOfTypeAtPosition(friendlyType,position);
	}

}

void GameMgr::CreateAsteroidField()
{
    int num = rand() % 15 + 11;
    for (int g = 0; g < num; g++)
    {
        int x = (rand() % 1000) - 500;
        int y = (rand() % 1000) - 500;
        int z = (rand() % 1000) - 500;
        engine->entityMgr->CreateEntityOfTypeAtPosition(asteroidDefault,Ogre::Vector3(x,y,z));

    }
}

