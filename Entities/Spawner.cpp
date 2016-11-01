#include "Spawner.h"

Spawner::Spawner(float *pos, int nlvl, Ogre::SceneNode *spawnerNode, Ogre::AnimationState *spawn)
  : ACharacter(), lvl(nlvl), spawingTime(4)
{
  position[0] = pos[0];
  position[1] = pos[1];
  position[2] = pos[2];
  _hp = 200;
  _maxHp = 200;
  _speed = 0;
  _damage = 0;
  _name = "Spawner";
  _animations["die"] = 0;
  _animations["attack"] = 0;
  _animations["move"] = 0;
  _animations["spawn"] = spawn;
  _node = spawnerNode;
  timer.startTime();
  gui = 0;
  _isHero = false;
}

Spawner::~Spawner()
{
}

Ogre::AnimationState *
Spawner::move(const Ogre::Vector3 __attribute__((unused)) &v)
{
  return (_animations["move"]);
}

Ogre::AnimationState *
Spawner::attack()
{
  return (_animations["attack"]);
}

Ogre::AnimationState *
Spawner::die()
{
  return (_animations["die"]);
}

Ogre::AnimationState *
Spawner::spawn()
{
  return (_animations["spawn"]);
}

int
Spawner::getSpawingNumber() const
{
  return (SPAWING_NUMBER);
}

bool
Spawner::isSpawing()
{
  if (timer.getTimeElapsedSec() >= spawingTime)
    {
      timer.resetTime();
      timer.startTime();
      return (true);
    }
  return (false);
}

int
Spawner::getLvl() const
{
  return (lvl);
}


const float *
Spawner::getPos() const
{
  return (position);
}

AItem *
Spawner::onDie(Ogre::SceneManager *scene) const
{
  Ogre::SceneNode *node;
  Ogre::Entity *e;
  Ogre::Vector3 pos;
  Key * key;

  e = scene->createEntity("Key.mesh");
  pos = _node->getPosition();
  node = scene->getRootSceneNode()->createChildSceneNode(pos);
  node->attachObject(e);
  node->setScale(0.5, 0.5, 0.5);
  key = new Key(node);
  key->setAnim(e->getAnimationState("rotate"));
  return (key);
}
