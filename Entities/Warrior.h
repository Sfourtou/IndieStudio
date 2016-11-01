#ifndef GAUNTLET_WARRIOR_H
#define GAUNTLET_WARRIOR_H

#include <Ogre.h>
#include "ACharacter.h"
#include "AHero.h"

class Warrior : public ACharacter, public AHero {
public:
    Warrior(Ogre::SceneNode * entity, Ogre::AnimationState * move, Ogre::AnimationState * attack, Ogre::AnimationState * die, IAType type);
    virtual ~Warrior();
private:
public:
    virtual Ogre::AnimationState * move(const Ogre::Vector3 &pos);
    virtual Ogre::AnimationState * attack();
    virtual Ogre::AnimationState * die();
};


#endif //GAUNTLET_WARRIOR_H
