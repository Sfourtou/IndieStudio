#include "EntitiesFactory.h"
#include "Archer.h"
#include "Ghost.h"
#include "Grunt.h"
#include "Demon.h"
#include "Warrior.h"

EntitiesFactory::EntitiesFactory()
  : idx(0)
{
    // _creationMethods["Archer"] = &EntitiesFactory::createArcher;
    // _creationMethods["Ghost"] = &EntitiesFactory::createGhost;
}

EntitiesFactory::~EntitiesFactory() {
}

ACharacter * EntitiesFactory::createArcher(Ogre::SceneManager * scene, Ogre::Vector3 & pos, IAType type) {
    Archer *archer;

    Ogre::Entity * mArcher = scene->createEntity("Mage" + std::to_string(idx), "Lutin.mesh");

    Ogre::SceneNode * archerNode = scene->getRootSceneNode()->createChildSceneNode("Mage" + std::to_string(idx++), pos);
    archerNode->attachObject(mArcher);
    archer = new Archer(archerNode, mArcher->getAnimationState("move"), mArcher->getAnimationState("attack"), mArcher->getAnimationState("die"), type);
    return (archer);
}

ACharacter * EntitiesFactory::createWarrior(Ogre::SceneManager * scene, Ogre::Vector3 & pos, IAType type){
    Warrior *warrior;

    Ogre::Entity * mArcher = scene->createEntity("Warrior" + std::to_string(idx), "Warrior.mesh");
    Ogre::SceneNode * archerNode = scene->getRootSceneNode()->createChildSceneNode("Warrior" + std::to_string(idx++), pos);
    archerNode->scale(1.5, 1.5, 1.5);
    archerNode->attachObject(mArcher);
    warrior = new Warrior(archerNode, mArcher->getAnimationState("walk"), mArcher->getAnimationState("attack"), mArcher->getAnimationState("die"), type);
    return (warrior);
}

ACharacter * EntitiesFactory::createGhost(Ogre::SceneManager *scene, Ogre::Vector3 & pos) {
    Ghost *ghost;

    Ogre::Entity *mGhost = scene->createEntity("Ghost" + std::to_string(idx), "Ghost.mesh");
    Ogre::SceneNode * ghostNode = scene->getRootSceneNode()->createChildSceneNode("Ghost" + std::to_string(idx++), pos);
    ghostNode->scale(0.4, 0.4, 0.4);
    ghostNode->attachObject(mGhost);
    ghost = new Ghost(ghostNode, mGhost->getAnimationState("walk"), NULL, NULL);
    return (ghost);
}

ACharacter * EntitiesFactory::createGrunt(Ogre::SceneManager * scene, Ogre::Vector3 &pos) {
    Grunt *grunt;

    Ogre::Entity *mGrunt = scene->createEntity("Grunt" + std::to_string(idx), "Ogre.mesh");
    Ogre::SceneNode * gruntNode = scene->getRootSceneNode()->createChildSceneNode("Grunt" + std::to_string(idx++), pos);
    gruntNode->attachObject(mGrunt);
    grunt = new Grunt(gruntNode, mGrunt->getAnimationState("walk"), mGrunt->getAnimationState("attack"), mGrunt->getAnimationState("die"));
    return (grunt);
}

ACharacter * EntitiesFactory::createSorcerer(Ogre::SceneManager *scene, Ogre::Vector3 &pos)  {
    Demon * demon;

    Ogre::Entity *mDemon = scene->createEntity("Demon" + std::to_string(idx), "MyDemon.mesh");
    Ogre::SceneNode *demonNode = scene->getRootSceneNode()->createChildSceneNode("Demon" + std::to_string(idx++), pos);
    demonNode->scale(0.5, 0.5, 0.5);
    demonNode->attachObject(mDemon);
    demon = new Demon(demonNode, mDemon->getAnimationState("walk"), mDemon->getAnimationState("attack"), mDemon->getAnimationState("die"));
    return (demon);
}

Spawner *
EntitiesFactory::createSpawner(Ogre::SceneManager *scene, Ogre::Vector3 &pos)
{
  Spawner *spawner;
  float   tab[3];

  tab[0] = pos.x;
  tab[1] = pos.y;
  tab[2] = pos.z;
  Ogre::Entity * mSpawner = scene->createEntity(std::string("Spawner") + std::to_string(idx), std::string("Chest.mesh"));
  Ogre::SceneNode * sNode = scene->getRootSceneNode()->createChildSceneNode(std::string("Spawner") + std::to_string(idx++), pos);
  sNode->setScale(3, 3, 3);
  sNode->attachObject(mSpawner);
  spawner = new Spawner(tab, 1, sNode, mSpawner->getAnimationState("spawn"));
  return (spawner);
}

AItem *
EntitiesFactory::createKey(Ogre::SceneManager *scene, Ogre::Vector3 &pos)
{
  Ogre::SceneNode *node;
  Ogre::Entity *e;
  AItem        *item;

  e = scene->createEntity("Key.mesh");
  node = scene->getRootSceneNode()->createChildSceneNode(pos);
  node->attachObject(e);
  node->setScale(0.5, 0.5, 0.5);
  item = new Key(node);
  item->setAnim(e->getAnimationState("rotate"));
  return (item);
}

AItem *
EntitiesFactory::createPotion(Ogre::SceneManager *scene, Ogre::Vector3 &pos)
{
  Ogre::SceneNode *node;
  Ogre::Entity *e;
  AItem *item;

  e = scene->createEntity("LifePotion.mesh");
  node = scene->getRootSceneNode()->createChildSceneNode(pos);
  node->attachObject(e);
  node->setScale(0.5, 0.5, 0.5);
  item = new Potion(node);
  item->setAnim(e->getAnimationState("rotate"));
  return (item);
}

AItem *
EntitiesFactory::createSpeedPowerUp(Ogre::SceneManager *scene, Ogre::Vector3 &pos)
{
  Ogre::SceneNode *node;
  Ogre::Entity *e;
  AItem *item;

  e = scene->createEntity("Claquette.mesh");
  node = scene->getRootSceneNode()->createChildSceneNode(pos);
  node->attachObject(e);
  node->setScale(10, 10, 10);
  item = new SpeedPowerUp(node);
  item->setAnim(e->getAnimationState("rotate"));
  return (item);
}

AItem *
EntitiesFactory::createDamagePowerUp(Ogre::SceneManager *scene, Ogre::Vector3 &pos)
{
  Ogre::SceneNode *node;
  Ogre::Entity *e;
  AItem       *item;

  e = scene->createEntity("Sword.mesh");
  node = scene->getRootSceneNode()->createChildSceneNode(pos);
  node->attachObject(e);
  node->setScale(1, 1, 1);
  item = new DamagePowerUp(node);
  item->setAnim(e->getAnimationState("rotate"));
  return (item);
}
