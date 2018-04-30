/*
 * Aspect.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <Aspect.h>
#include <Entity381.h>  //Aspect includes Entity381.h
#include <DebugDrawer.h>


Aspect::Aspect(Entity381 *ent){
	entity = ent;
}

Aspect::~Aspect(){

}

void Aspect::Tick(float dt){

}

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
