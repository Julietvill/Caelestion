#ifndef __EntityMgr_h_
#define __EntityMgr_h_

#include <vector>
#include <Mgr.h>
#include <Entity381.h>
#include <Types381.h>

class EntityMgr: public Mgr {
public:
  EntityMgr(Engine *engine);
  virtual ~EntityMgr();

  //Engine *engine;

  std::vector<Entity381*> entities;

  std::vector<Entity381*> projectiles;

  Entity381* playerEntity;
  Entity381* caelestion;
  Entity381* yggdrasil;

  Ogre::Vector3 yggdrasilPos;
  Ogre::Vector3 caelestionPos;

  //Ogre::SceneManager *sceneMgr;

  void CreateEntityOfTypeAtPosition(EntityTypes type, Ogre::Vector3 pos);
  void CreateProjectile(Ogre::Vector3 pos, Weapon* owner);


  void Tick(float dt);

protected:

private:
  int entCount;
  int projCount;
};

#endif // #ifndef __EntityMgr_h_
