#ifndef GAUNTLET_ARCHER_H
#define GAUNTLET_ARCHER_H
# include "ACharacter.h"
# include "AHero.h"

class Archer : public ACharacter, public AHero
{
public:
    Archer(Ogre::SceneNode * entity, Ogre::AnimationState * move, Ogre::AnimationState * attack, Ogre::AnimationState * die, IAType type);
    virtual ~Archer();
private:
public:
    virtual Ogre::AnimationState * move(const Ogre::Vector3 &pos);
    virtual Ogre::AnimationState * attack();
    virtual Ogre::AnimationState * die();
};

#endif //GAUNTLET_ARCHER_H
