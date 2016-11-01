#ifndef GAUNTLET_DEMON_H
#define GAUNTLET_DEMON_H


#include <Ogre.h>
#include "ACharacter.h"

class Demon : public ACharacter{
public:
    Demon(Ogre::SceneNode * entity, Ogre::AnimationState * move, Ogre::AnimationState * attack, Ogre::AnimationState * die);
    virtual ~Demon();
private:
public:
    virtual Ogre::AnimationState * move(const Ogre::Vector3 &pos);
    virtual Ogre::AnimationState * attack();
    virtual Ogre::AnimationState * die();
};


#endif //GAUNTLET_DEMON_H
