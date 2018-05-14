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
	Aspect(own),
	dmgOnHit(dmg),
	placement(placement),
	fire(false)
{

}

Weapon::~Weapon(){}

void Weapon::Fire(){}

void Weapon::Tick(float dt){}



T1Killray::T1Killray(Ogre::Vector3 placement, Entity381* own):
		Weapon(800, placement, own)
{
	fire = false;
}

T1Killray::~T1Killray(){}

void T1Killray::Fire()
{
	fire = true;
}

void T1Killray::Tick(float dt)
{
	if (fire)
	{
		Entity381* owner = entity;
		//owner->engine->soundMgr->playSelectionSound(*owner);
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

	fire = false;
}


T1Projectile::T1Projectile(Ogre::Vector3 placement, Entity381* own):
		Weapon(50, placement, own)
{
	projmeshfilename = "cube.mesh";

	cooldown = .5f;
	coolstate = 0.f;
	own->fireSound = "Laser_light.wav";
	own->fireAudioID = 2;
}

T1Projectile::~T1Projectile(){}

void T1Projectile::Fire()
{
	if(coolstate <= 0.f)
	{
		fire = true;
	}
}

void T1Projectile::Tick(float dt)
{
	if(coolstate > 0.f) coolstate -= dt;

	if (fire)
	{
		coolstate = cooldown;
		Entity381* owner = entity;
		if(owner->engine->entityMgr->playerEntity == owner)	owner->engine->soundMgr->playLightSound(owner);

		Ogre::Vector3 realFirept = owner->actualFacing.Inverse() * placement;

		realFirept = realFirept + owner->position;

		//std::cout << "FIRE FROM" << realFirept << std::endl;

		entity->engine->entityMgr->CreateProjectile(realFirept, this);
	}

	fire = false;
}

T2Projectile::T2Projectile(Ogre::Vector3 placement, Entity381* own):
		T1Projectile(placement, own)
{
	dmgOnHit = 100;
	cooldown = 1.f;
	own->fireSound = "Laser_light.wav";
	own->fireAudioID = 2;
}

T2Projectile::~T2Projectile(){};

T3Projectile::T3Projectile(Ogre::Vector3 placement, Entity381* own):
		T1Projectile(placement, own)
{
	dmgOnHit = 200;
	cooldown = 1.5f;
	own->fireSound = "Laser_heavy.wav";
	own->fireAudioID = 3;
}

T3Projectile::~T3Projectile(){};

TestMcHuge::TestMcHuge(Ogre::Vector3 placement, Entity381* own):
		T1Projectile(placement, own)
{
	dmgOnHit = 200000;
	cooldown = 0.5f;
	own->fireSound = "Laser_heavy.wav";
	own->fireAudioID = 3;
}

TestMcHuge::~TestMcHuge(){};


