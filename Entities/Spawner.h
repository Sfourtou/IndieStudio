#ifndef SPAWNER_H_
# define SPAWNER_H_
# include "ACharacter.h"
# include "../Timer.h"
# define SPAWING_NUMBER 5
# define MIN_SPAWING_TIME_SEC 10

class Spawner : public ACharacter
{
public:
  Spawner(float *pos, int lvl, Ogre::SceneNode *SpawnerNode, Ogre::AnimationState *spawn);
  ~Spawner();
  Ogre::AnimationState * move(const Ogre::Vector3 &pos);
  Ogre::AnimationState * attack();
  Ogre::AnimationState * die();
  Ogre::AnimationState * spawn();
  int                       getSpawingNumber() const;
  bool                       isSpawing();
  int                       getLvl() const;
  const float * getPos() const;
  AItem *onDie(Ogre::SceneManager *scene) const;

private:
  float       position[3];
  int         lvl;
  Timer       timer;
  int         spawingTime;
};

#endif /* SPAWNER_H_ */
