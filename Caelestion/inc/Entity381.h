#ifndef __Entity381_h_
#define __Entity381_h_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <Aspect.h>
#include <Types381.h>

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


  //dynamic data
  Ogre::Vector3 position;
  Ogre::Vector3 startPosition;
  Ogre::Vector3 velocity;
  float desiredHeading;

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
  std::string soundFile;
  bool playSound;
  unsigned int auioID;
  bool didSelectSoundPlay;

  Ogre::Vector3 enemyHQ;
  std::vector<Ogre::Vector3> weaponPositions;

  bool enemy;

  void Init();

  void Tick(float dt);

  void Lobotomize();

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
#endif // #ifndef __Entity381_h_
