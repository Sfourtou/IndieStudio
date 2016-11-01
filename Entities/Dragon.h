#ifndef GAUNTLET_DRAGON_H
#define GAUNTLET_DRAGON_H


#include "ACharacter.h"

class Dragon : public ACharacter{
public:
    Dragon(Ogre::SceneNode *node, Ogre::AnimationState *intro, Ogre::AnimationState *attack1,
               Ogre::AnimationState *attack2, Ogre::AnimationState *attack3, Ogre::AnimationState *die);
    ~Dragon();
public:
    virtual Ogre::AnimationState * move(const Ogre::Vector3 &pos);
    virtual Ogre::AnimationState * attack();
    virtual Ogre::AnimationState * die();
    virtual Projectile * attack(Ogre::SceneManager * mSceneManager);
    Ogre::AnimationState *intro();
    Projectile *threeProjectiles(Ogre::SceneManager *sceneMgr, const Ogre::Vector3 &pos);
    AItem *onDie(Ogre::SceneManager *scene) const;
    void setDead();
    bool isDead() const;
private:
    bool _isDead;
};


#endif //GAUNTLET_DRAGON_H
