/*
 * GameMgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef GAMEMGR_H_
#define GAMEMGR_H_

#include <Mgr.h>
#include <Types381.h>

class GameMgr: public Mgr {
public:
	GameMgr(Engine *engine);
	virtual ~GameMgr();

	void Init();
	void LoadLevel();

	void MakeGround();
	void MakeSky();
	void MakeEntities(EntityTypes friendlyType, EntityTypes enemyType, int amount);
	void Tick(float dt);

	bool waveOneUnlocked;
	bool waveTwoUnlocked;
	bool waveThreeUnlocked;

	Ogre::Plane oceanSurface;
	int points;

};

#endif /* GAMEMGR_H_ */
