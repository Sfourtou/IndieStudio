#include "Entities/ACharacter.h"
#include "Projectile.h"


Projectile::Projectile(ACharacter *owner, Ogre::SceneNode *entity, Ogre::AnimationState *anim, float range)
        : _owner(owner), _node(entity),  _pos(owner->getPosition() + Ogre::Vector3::UNIT_Y), _dir(owner->getLastDir()), _dist(0), _speed(20.0f), _anim(anim), _range(range)
{
    owner->setNbProjectile(1);
    _damage = owner->getDamage();
    _isHero = owner->isHero();
    Ogre::Vector3 apa = _node->getPosition() + _dir - _node->getPosition();
    apa.normalise();
    apa.y = 0;
    Ogre::Vector3 test = _node->getOrientation() * Ogre::Vector3::UNIT_Z;
    Ogre::Quaternion q = test.getRotationTo(apa);
    _node->rotate(q);
}

Projectile::Projectile(ACharacter *owner, Ogre::SceneNode *entity, Ogre::AnimationState *anim, float range, Ogre::Vector3 dir)
        : _owner(owner), _node(entity),  _pos(owner->getPosition() + Ogre::Vector3::UNIT_Y), _dir(dir), _dist(0), _speed(20.0f), _anim(anim), _range(range)
{
    owner->setNbProjectile(1);
    _damage = owner->getDamage();
    _isHero = owner->isHero();
    Ogre::Vector3 apa = _node->getPosition() + dir - _node->getPosition();
    apa.normalise();
    apa.y = 0;
    Ogre::Vector3 test = _node->getOrientation() * Ogre::Vector3::UNIT_Z;
    Ogre::Quaternion q = test.getRotationTo(apa);
    _node->rotate(q);
}

Projectile::~Projectile() {
}

Ogre::SceneNode * Projectile::getNode() const {
    return _node;
}

int Projectile::getDamage() const {
    return _damage;
}

Ogre::Vector3 Projectile::getPos() const {
    return _node->getPosition();
}

Ogre::Vector3 Projectile::getDir() const {
    return _dir;
}

Ogre::AnimationState *    Projectile::move(Ogre::Real timeSinceLastFrame)
{
    _dist += _speed * timeSinceLastFrame;
    _node->translate((_dir * timeSinceLastFrame) * _speed);
    return _anim;
}

float   Projectile::getDistance() const
{
    return _dist;
}

float Projectile::getRange() const {
    return _range;
}

float Projectile::getSpeed() const {
    return _speed;
}

bool Projectile::isHero() const {
    return _isHero;
}
