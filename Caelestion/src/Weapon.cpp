/*
 * Weapon.cpp
 *
 *  Created on: May 2, 2018
 *      Author: julietv
 */

#include <Weapon.h>
#include<Entity381.h>
#include <EntityMgr.h>
#include <SoundMgr.h>
#include <GameMgr.h>


Weapon::Weapon(int dmg, Ogre::Vector3 placement, Entity381* own) :
	dmgOnHit(dmg),
	placement(placement),
	owner(own)
{

}

Weapon::~Weapon(){}

void Weapon::Fire(float dt){}

T1Killray::T1Killray(Ogre::Vector3 placement, Entity381* own):
		Weapon(800, placement, own)
{

}

T1Killray::~T1Killray(){}

void T1Killray::Fire(float dt)
{
	owner->engine->soundMgr->playSelectionSound(*owner);
	Ogre::Vector3 realFirept = owner->actualFacing.Inverse() * placement;
	Ogre::Vector3 endPoint = placement + Ogre::Vector3(0,0,-10000);
	endPoint = owner->actualFacing.Inverse() * endPoint;
	realFirept = realFirept + owner->position;
	endPoint = endPoint + owner->position;

	Ogre::Ray rc;
	rc.setOrigin(realFirept);
	//std::cout << "FIRE FROM" << realFirept << std::endl;
	rc.setDirection((-1) * owner->actualFacing.zAxis());

	int s = owner->engine->entityMgr->entities.size();
	Entity381* cur;
	for (int i = 0; i < s; i ++)
	{
		cur = owner->engine->entityMgr->entities[i];
		if (cur != owner && rc.intersects(cur->sceneNode->_getWorldAABB()).first)
		{
			std::cout << "HIT" << std::endl;
			cur->currentHealth -= dmgOnHit*dt;
			if(owner == owner->engine->entityMgr->playerEntity)
			{
				if (cur->currentHealth <= 0)
				{
					owner->engine->gameMgr->points += cur->pointValue;
				}
			}
		}

	}
}

T1Projectile::T1Projectile(Ogre::Vector3 placement, Entity381* own):
		Weapon(1000, placement, own)
{

	cooldown = 1.5;
	coolstate = 0.f;
}

T1Projectile::~T1Projectile(){}

void T1Projectile::Fire(float dt)
{

}

