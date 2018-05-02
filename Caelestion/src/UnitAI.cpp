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

using namespace std;

UnitAI::UnitAI(Entity381* ent)
: Aspect(ent)
{
	MoveTo* enemyHQ = new MoveTo(entity);
	enemyHQ->dest = entity->enemyHQ;
	listOfCommands.push(enemyHQ);
	distanceSqr = 0;
	avoiding = false;
}

UnitAI::~UnitAI(){

}
void UnitAI::Tick(float dt){
	if( !listOfCommands.empty() ){

		listOfCommands.top()->Tick(dt);

		//check the distances between the entities, for avoidance and attacking
		for( unsigned int index = 0; index < entity->engine->entityMgr->entities.size(); index++){
			distanceSqr = entity->position.squaredDistance(entity->engine->entityMgr->entities[index]->position);
			if( entity->enemy == entity->engine->entityMgr->entities[index]->enemy )
			{
				if( distanceSqr < 2500 && entity->engine->entityMgr->entities[index] != this->entity){
					avoiding = true;
					Avoid* avoid = new Avoid(entity, entity->engine->entityMgr->entities[index]);
					listOfCommands.push(avoid);
				}
			}
			else{
				if( distanceSqr < 62500 && entity->engine->entityMgr->entities[index] != this->entity){
					Attack* attackEnemy = new Attack(entity, entity->engine->entityMgr->entities[index]);
					listOfCommands.push(attackEnemy);
				}
			}
		}

		if( listOfCommands.top()->isComplete ){
			listOfCommands.pop();
			avoiding = false;
		}
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


