/*
 * UnitAI.h
 *
 *  Created on: Mar 28, 2018
 *      Author: julietv
 */

#ifndef INC_UNITAI_H_
#define INC_UNITAI_H_

#include <Aspect.h>
#include <Command.h>
#include <queue>

class UnitAI : public Aspect {
public:
	UnitAI(Entity381* ent);
	~UnitAI();
	void Tick(float dt);


	void SetCommand(Command* c);
	void AddCommand(Command* c);
	void clear();

	std::queue<Command*> listOfCommands;

private:
};


#endif /* INC_UNITAI_H_ */
