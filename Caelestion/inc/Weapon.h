/*
 * Weapon.h
 *
 *  Created on: May 2, 2018
 *      Author: julietv
 */

#ifndef INC_WEAPON_H_
#define INC_WEAPON_H_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
class Entity381;    //Forward declaration of the Entity381 class

class Weapon
{
public:
	Weapon(int dmg, Ogre::Vector3 placement, Entity381* own);
	virtual ~Weapon();

	virtual void Fire(float dt);

	int dmgOnHit;
	Ogre::Vector3 placement;
	Entity381* owner;
protected:
};


class T1Killray : public Weapon
{
public:
	T1Killray(Ogre::Vector3 placement, Entity381* own);
	~T1Killray();

	void Fire(float dt);
};

#endif /* INC_WEAPON_H_ */
