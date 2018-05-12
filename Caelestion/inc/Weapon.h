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
#include <Aspect.h>

class Entity381;    //Forward declaration of the Entity381 class

class Weapon : public Aspect
{
public:
	Weapon(int dmg, Ogre::Vector3 placement, Entity381* own);
	virtual ~Weapon();

	virtual void Fire();
	virtual void Tick(float dt);


	int dmgOnHit;
	Ogre::Vector3 placement;
	bool fire;

protected:
};


class T1Killray : public Weapon
{
public:
	T1Killray(Ogre::Vector3 placement, Entity381* own);
	~T1Killray();

	void Fire();
	void Tick(float dt);
};


class T1Projectile : public Weapon
{
public:
	T1Projectile(Ogre::Vector3 placement, Entity381* own);
	~T1Projectile();

	void Fire();
	void Tick(float dt);


	float cooldown;
	float coolstate;

    std::string projmeshfilename;
	std::string projmatname;

};


#endif /* INC_WEAPON_H_ */
