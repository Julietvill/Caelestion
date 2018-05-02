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
#include <stack>

class UnitAI : public Aspect {
public:
	UnitAI(Entity381* ent);
	~UnitAI();
	void Tick(float dt);


	void addCommand(Command* c);
	void clear();

	float distanceSqr;
	std::stack<Command*> listOfCommands;
	bool avoiding;

private:
};


#endif /* INC_UNITAI_H_ */
