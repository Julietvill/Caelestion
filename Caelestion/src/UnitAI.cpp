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
				if( distanceSqr < 2500 && entity->engine->entityMgr->entities[index] != this->entity && !avoiding){
					Avoid* avoid = new Avoid(this,entity, entity->engine->entityMgr->entities[index]);
					listOfCommands.push(avoid);
				}
			}

			else{
				if( distanceSqr < 62500 && entity->engine->entityMgr->entities[index] != this->entity && !attacking){
					Attack* attackEnemy = new Attack(this,entity, entity->engine->entityMgr->entities[index]);
					listOfCommands.push(attackEnemy);
				}

				else if( distanceSqr < 2500 && entity->engine->entityMgr->entities[index] != this->entity){
					Avoid* avoid = new Avoid(this,entity, entity->engine->entityMgr->entities[index]);
					listOfCommands.push(avoid);
				}
			}

		}

		if( listOfCommands.top()->isComplete ){
			listOfCommands.pop();
		}
	}
	else{
		MoveTo* enemyHQ = new MoveTo(this,entity);
		if( !entity->enemy)
			enemyHQ->dest = entity->engine->entityMgr->yggdrasilPos;
		else
			enemyHQ->dest = entity->engine->entityMgr->caelestionPos;
		listOfCommands.push(enemyHQ);
		distanceSqr = 0;
		avoiding = false;
		attacking = false;
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


