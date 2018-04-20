/*
 * UnitAI.cpp
 *
 *  Created on: Mar 28, 2018
 *      Author: julietv
 */


#include <UnitAI.h>
#include <Entity381.h>

UnitAI::UnitAI(Entity381* ent)
: Aspect(ent)
{

}

UnitAI::~UnitAI(){

}
void UnitAI::Tick(float dt){
	if( !listOfCommands.empty() ){
		listOfCommands.front()->Tick(dt);
		if( listOfCommands.front()->isComplete ){
			listOfCommands.pop();
		}
	}
}

void UnitAI::SetCommand(Command* c){
	this->clear();
	listOfCommands.push(c);
}
void UnitAI::AddCommand(Command* c){
	listOfCommands.push(c);
}


void UnitAI::clear(){
	while( !listOfCommands.empty() ){
		listOfCommands.pop();
	}
}


