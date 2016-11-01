#ifndef GAUNTLET_PROJECTILE_H
#define GAUNTLET_PROJECTILE_H


#include <Ogre.h>

class ACharacter;

class Projectile {
private:

    Ogre::SceneNode *_node;
    ACharacter      *_owner;
    Ogre::Vector3   _pos;
    float           _speed;
    Ogre::Vector3   _dir;
    float           _dist;
    Ogre::AnimationState *_anim;
    float           _range;
    int              _damage;
    bool              _isHero;

public:
    Projectile(ACharacter *, Ogre::SceneNode *entity, Ogre::AnimationState *, float range);
    Projectile(ACharacter *owner, Ogre::SceneNode *entity, Ogre::AnimationState *anim, float range, Ogre::Vector3 dir);
    ~Projectile();
    Ogre::SceneNode *getNode() const;
    int             getDamage() const;
    Ogre::Vector3   getPos() const;
    Ogre::Vector3   getDir() const;
    Ogre::AnimationState           *move(Ogre::Real);
    float           getDistance() const;
    float           getRange() const;
    bool            isHero() const;

    float getSpeed() const;
};


#endif //GAUNTLET_PROJECTILE_H
