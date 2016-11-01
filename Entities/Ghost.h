#ifndef GAUNTLET_GHOST_H
#define GAUNTLET_GHOST_H


#include <OGRE/Ogre.h>
#include "ACharacter.h"

class Ghost : public ACharacter{
public:
    Ghost(Ogre::SceneNode * entity, Ogre::AnimationState * move, Ogre::AnimationState * attack, Ogre::AnimationState * die);
    virtual ~Ghost();
private:
public:
    virtual Ogre::AnimationState * move(const Ogre::Vector3 &pos);
    virtual Ogre::AnimationState * attack();
    virtual Ogre::AnimationState * die();
};


#endif //GAUNTLET_GHOST_H
