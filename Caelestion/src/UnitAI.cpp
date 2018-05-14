/*
 * UnitAI.cpp
 *
 *  Created on: Mar 28, 2018
 *      Author: julietv
 */


#include <UnitAI.h>
#include <Entity381.h>
#include <Engine.h>
#include <EntityMgr.h>
#include <GameMgr.h>

using namespace std;

UnitAI::UnitAI(Entity381* ent)
: Aspect(ent)
{
	distanceSqr = 0;
}

UnitAI::~UnitAI(){

}
void UnitAI::Tick(float dt){
	if( !listOfCommands.empty() ){

		listOfCommands.top()->Tick(dt);

		//check the distances between the entities, for avoidance and attacking
		for( unsigned int index = 0; index < entity->engine->entityMgr->entities.size(); index++){
			distanceSqr = entity->position.squaredDistance(entity->engine->entityMgr->entities[index]->position);
			if( distanceSqr < 2500 && entity->engine->entityMgr->entities[index] != this->entity && !entity->avoiding){
				Avoid* avoid = new Avoid(entity, entity->engine->entityMgr->entities[index]);
				listOfCommands.push(avoid);
			}

			if( distanceSqr < 62500 &&
					entity->engine->entityMgr->entities[index] != this->entity &&
					!entity->attacking &&
					entity->enemy != entity->engine->entityMgr->entities[index]->enemy){
				if( entity->engine->entityMgr->entities[index]->entityType != asteroidDefault){
					if(!entity->enemy )
					{
						if(entity->engine->entityMgr->yggdrasil == entity->engine->entityMgr->entities[index] && entity->engine->gameMgr->waveThreeUnlocked){
							Attack* attackEnemy = new Attack(entity, entity->engine->entityMgr->entities[index]);
							listOfCommands.push(attackEnemy);
						}
						else if(entity->engine->entityMgr->yggdrasil != entity->engine->entityMgr->entities[index]){
							Attack* attackEnemy = new Attack(entity, entity->engine->entityMgr->entities[index]);
							listOfCommands.push(attackEnemy);
						}
					}
					else{
						Attack* attackEnemy = new Attack(entity, entity->engine->entityMgr->entities[index]);
						listOfCommands.push(attackEnemy);
					}
				}
			}
		}
		if( listOfCommands.top()->isComplete ){
			listOfCommands.pop();
		}
	}
	else{
		MoveTo* enemyHQ = new MoveTo(entity);
		if( !entity->enemy)
			enemyHQ->dest = entity->engine->entityMgr->yggdrasilPos;
		else
			enemyHQ->dest = entity->engine->entityMgr->caelestionPos;
		listOfCommands.push(enemyHQ);
		distanceSqr = 0;
	}

}

void UnitAI::addCommand(Command* c){
	listOfCommands.push(c);
}

void UnitAI::clear(){
	while( !listOfCommands.empty() ){
		listOfCommands.pop();
	}
}


