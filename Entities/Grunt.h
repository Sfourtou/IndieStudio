#ifndef GAUNTLET_GRUNT_H
#define GAUNTLET_GRUNT_H

#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneNode.h>
#include "ACharacter.h"

class Grunt : public ACharacter{
    public:
    Grunt(Ogre::SceneNode * entity, Ogre::AnimationState * move, Ogre::AnimationState * attack, Ogre::AnimationState * die);
    virtual ~Grunt();
private:
public:
    virtual Ogre::AnimationState * move(const Ogre::Vector3 &pos);
    virtual Ogre::AnimationState * attack();
    virtual Ogre::AnimationState * die();
};


#endif //GAUNTLET_GRUNT_H
