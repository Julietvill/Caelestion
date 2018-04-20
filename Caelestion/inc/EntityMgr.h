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

  std::vector<Entity381*> enemies;
  std::vector<Entity381*> friendlies;
  Entity381* playerEntity;

  //Ogre::SceneManager *sceneMgr;

  void CreateEntityOfTypeAtPosition(EntityTypes type, Ogre::Vector3 pos);

  void Tick(float dt);

protected:

private:
  int friendlyCount;
  int enemyCount;

};

#endif // #ifndef __EntityMgr_h_
