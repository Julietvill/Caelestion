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


GameMgr::GameMgr(Engine *engine): Mgr(engine) {

}

GameMgr::~GameMgr() {
}

void GameMgr::Init(){
	  engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	  engine->gfxMgr->mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	  Ogre::Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
	  light->setPosition(20.0, 80.0, 50.0);

	  //engine->gfxMgr->MakeGround();
	  engine->gfxMgr->MakeSky();
	  engine->entityMgr->CreateEntityOfTypeAtPosition(friendlyTypeOne,Ogre::Vector3(0,0,0));
	  engine->entityMgr->playerEntity = engine->entityMgr->friendlies[0];

	  //engine->gfxMgr->cameraFollow = engine->entityMgr->playerEntity;

	  // a fixed point in the ocean so you can see relative motion

	  Ogre::Entity* ogreEntityFixed = engine->gfxMgr->mSceneMgr->createEntity("robot.mesh");
	  Ogre::SceneNode* sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 100, -200));
	  sceneNode->attachObject(ogreEntityFixed);
	  sceneNode->showBoundingBox(true);

}

void GameMgr::LoadLevel(){

}

void GameMgr::MakeEntities(){

}

