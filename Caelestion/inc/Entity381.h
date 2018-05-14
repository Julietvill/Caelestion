#ifndef __Entity381_h_
#define __Entity381_h_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <Aspect.h>
#include <Types381.h>
#include <Weapon.h>

#include <Engine.h>

class Entity381
{
public:
  Entity381(Engine *engine, Ogre::Vector3 pos, int identity);
  virtual ~Entity381();

  Engine *engine;

  //static data
  int identity;
  std::string name;
  std::string meshfilename;
  std::string matname;
  Ogre::SceneNode* sceneNode;
  Ogre::Entity*    ogreEntity;
  float turnRate, climbRate;
  float minAltitude, maxAltitude;
  int pointValue;
  bool enemy;
  int maxHealth;


  //dynamic data
  Ogre::Vector3 position;
  Ogre::Vector3 startPosition;
  Ogre::Vector3 velocity;
  float desiredHeading;
  int currentHealth;
  bool hit;
  bool attacking;
  bool avoiding;

  //values for Quaternion math (both dynamic)
  Ogre::Quaternion actualFacing;
  Ogre::Vector3 desiredRotation;

  int acc; //For player control. -1 is decelerate, 1 is accelerate. 0 is no control action.

  float heading, speed;
  float altitude, desiredAltitude;

  //if we decide to use this it can show the current target and help with shooting?
  bool isSelected;

  EntityTypes entityType;

  std::vector<Aspect* > aspects;

  //sound
  std::string deathSound;
  std::string fireSound;
  bool playSound;
  bool fireDone;
  unsigned int fireAudioID;
  unsigned int deathAudioID;
  bool deathDone;

  std::vector<Weapon*> weapons; //nevuh enough dakka
  bool killMe;
  Weapon* owner;

  int count;
  float age;

  void Init();
  virtual void Tick(float dt);
  void Lobotomize();
  void switchPlayerEnt( EntityTypes type);

protected:


};

//-------------------------------------------------------------------------------------------------------------------------------

class friendlyOne : public Entity381{
public:
	friendlyOne(Engine *engine, Ogre::Vector3 pos, int identity);
	~friendlyOne();
private:
};
//-------------------------------------------------------------------------------------------------------------------------------

class friendlyTwo : public Entity381{
public:
	friendlyTwo(Engine *engine, Ogre::Vector3 pos, int identity);
	~friendlyTwo();
private:
};
//-------------------------------------------------------------------------------------------------------------------------------

class friendlyThree : public Entity381{
public:
	friendlyThree(Engine *engine, Ogre::Vector3 pos, int identity);
	~friendlyThree();
private:
};
//-------------------------------------------------------------------------------------------------------------------------------

class caelestionStation : public Entity381{
public:
	caelestionStation(Engine *engine, Ogre::Vector3 pos, int identity);
	~caelestionStation();
private:
};
//-------------------------------------------------------------------------------------------------------------------------------

class enemyOne : public Entity381{
public:
	enemyOne(Engine *engine, Ogre::Vector3 pos, int identity);
	~enemyOne();
private:
};
//-------------------------------------------------------------------------------------------------------------------------------

class enemyTwo : public Entity381{
public:
	enemyTwo(Engine *engine, Ogre::Vector3 pos, int identity);
	~enemyTwo();
private:
};
//-------------------------------------------------------------------------------------------------------------------------------

class enemyThree : public Entity381{
public:
	enemyThree(Engine *engine, Ogre::Vector3 pos, int identity);
	~enemyThree();
private:
};
//-------------------------------------------------------------------------------------------------------------------------------

class Yggdrasil : public Entity381{
public:
	Yggdrasil(Engine *engine, Ogre::Vector3 pos, int identity);
	~Yggdrasil();
private:
};

//RANDOM SPACE JUNK//-------------------------------------------------------------------------------------------------------
class Asteroid : public Entity381{
public:
	Asteroid(Engine *engine, Ogre::Vector3 pos, int identity);
	~Asteroid();
};

//PROJECTILES//-----------------------------------------------------------------------------------------------------------------
class Projectile : public Entity381{
public:
	Projectile(Engine* engine, Ogre::Vector3 pos, int identity, Weapon* owner);
	void Tick(float dt);
	~Projectile();

	float agelim; //Cap for lifetime.
private:
};

#endif // #ifndef __Entity381_h_
