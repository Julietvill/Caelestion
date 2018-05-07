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

}

GameMgr::~GameMgr() {
}

void GameMgr::Init(){
	  engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	  engine->gfxMgr->mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	  Ogre::Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
	  light->setPosition(20.0, 80.0, 50.0);

	  engine->gfxMgr->MakeSky();
	  engine->entityMgr->CreateEntityOfTypeAtPosition(friendlyTypeOne,Ogre::Vector3(0,0,0));
	  engine->entityMgr->playerEntity = engine->entityMgr->entities[0];
	  engine->entityMgr->playerEntity->Lobotomize();

	  //using this entity for AI obervation
	  engine->entityMgr->CreateEntityOfTypeAtPosition(friendlyTypeOne,Ogre::Vector3(0,0,-100));
	  engine->entityMgr->CreateEntityOfTypeAtPosition(friendlyTypeOne,Ogre::Vector3(0,0,-100));

	  engine->entityMgr->CreateEntityOfTypeAtPosition(enemyTypeOne,Ogre::Vector3(0,0,100));
	  engine->entityMgr->CreateEntityOfTypeAtPosition(enemyTypeOne,Ogre::Vector3(0,0,100));



	  // a fixed point in the ocean so you can see relative motion
	  Ogre::Entity* ogreEntityFixed = engine->gfxMgr->mSceneMgr->createEntity("Asteroid_1.mesh");
	  Ogre::SceneNode* sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 0, 0));
	  sceneNode->attachObject(ogreEntityFixed);
	  sceneNode->showBoundingBox(true);
	  sceneNode->setScale(25,25,25);

	  //MakeEntities();
}

void GameMgr::LoadLevel(){

}

void GameMgr::MakeEntities(){

	//change the position, it can now be the same
	Ogre::Vector3 position(-500, 0, -750);

	for( int i = 0; i < 7; i++){
		  engine->entityMgr->CreateEntityOfTypeAtPosition(enemyTypeOne,position);
	}

	for( int i = 0; i < 7; i++){
		  engine->entityMgr->CreateEntityOfTypeAtPosition(friendlyTypeOne,position);
	}

}

