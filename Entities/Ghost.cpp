#include "Ghost.h"

Ghost::Ghost(Ogre::SceneNode * ghostNode, Ogre::AnimationState * move, Ogre::AnimationState * attack, Ogre::AnimationState * die)
{
    _name = "Ghost";
    _hp = 40;
    _maxHp = 40;
    _keyCount = 0;
    _speed = 10;
    _damage = 40;
    _range = 2;
    _node = ghostNode;
    _animations["move"] = move;
    _animations["attack"] = attack;
    _animations["die"] = die;
    gui = 0;
    _attack = EXPLODE;
    _isHero = false;

}

Ghost::~Ghost()
{
}

Ogre::AnimationState * Ghost::attack()
{
    return _animations["attack"];
}

Ogre::AnimationState * Ghost::move(const Ogre::Vector3 & pos)
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

Ogre::AnimationState * Ghost::die()
{
    return _animations["die"];
}
