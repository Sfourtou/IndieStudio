#ifndef GAUNTLET_ENTITIESFACTORY_H
#define GAUNTLET_ENTITIESFACTORY_H


#include <string>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>
#include "../Scene.h"
#include "AHero.h"
#include "Spawner.h"
#include "ACharacter.h"
#include "../Key.h"
#include "../Potion.h"
#include "../SpeedPowerUp.h"
#include "../DamagePowerUp.h"

class EntitiesFactory {
typedef ACharacter * (EntitiesFactory::*ptr_method)(Ogre::SceneManager *, Ogre::Vector3 & pos);
public:
    EntitiesFactory();
    ~EntitiesFactory();
private:
    int idx;
    std::map<std::string, ptr_method> _creationMethods;
public:
    ACharacter * createArcher(Ogre::SceneManager *mSceneMgr, Ogre::Vector3 & pos, IAType type);
    ACharacter * createGhost(Ogre::SceneManager * mSceneMgr, Ogre::Vector3 & pos);
    ACharacter * createGrunt(Ogre::SceneManager * mSceneMgr, Ogre::Vector3 & pos);
    ACharacter * createSorcerer(Ogre::SceneManager * mSceneMgr, Ogre::Vector3 & pos);
public:
    Spawner    * createSpawner(Ogre::SceneManager *mSceneMgr, Ogre::Vector3 & pos);
    AItem       * createPotion(Ogre::SceneManager *mSceneMgr, Ogre::Vector3 & pos);
    AItem       * createSpeedPowerUp(Ogre::SceneManager *mSceneMgr, Ogre::Vector3 & pos);
    AItem       * createDamagePowerUp(Ogre::SceneManager *mSceneMgr, Ogre::Vector3 & pos);
    AItem       * createKey(Ogre::SceneManager *mSceneMgr, Ogre::Vector3 & pos);

    ACharacter *createWarrior(Ogre::SceneManager *scene, Ogre::Vector3 &pos, IAType type);
};


#endif //GAUNTLET_ENTITIESFACTORY_H
