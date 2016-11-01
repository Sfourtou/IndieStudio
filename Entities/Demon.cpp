#include "Demon.h"

Demon::Demon(Ogre::SceneNode * DemonNode, Ogre::AnimationState * move, Ogre::AnimationState * attack, Ogre::AnimationState * die)
{
    _name = "Demon";
    _hp = 150;
    _maxHp = 150;
    _keyCount = 0;
    _speed = 7;
    _damage = 30;
    _range = 20;
    _node = DemonNode;
    _animations["move"] = move;
    _animations["attack"] = attack;
    _animations["die"] = die;
    gui = 0;
    _attack = RANGE;
    _isHero = false;
}

Demon::~Demon()
{
}

Ogre::AnimationState * Demon::attack()
{
    return _animations["attack"];
}

Ogre::AnimationState * Demon::move(const Ogre::Vector3 & pos)
{
    if (pos.x == 0 && pos.y == 0 && pos.z == 0)
        return (NULL);
    _node->resetOrientation();
    Ogre::Vector3 apa = _node->getPosition() + pos - _node->getPosition();
    apa.normalise();
    apa.y = 0;
    Ogre::Vector3 test = _node->getOrientation() * Ogre::Vector3::UNIT_Z;
    Ogre::Quaternion q = test.getRotationTo(apa);
    _node->rotate(q);
    _node->translate(pos * _speed);
    return _animations["move"];
}

Ogre::AnimationState * Demon::die()
{
    return _animations["die"];
}
