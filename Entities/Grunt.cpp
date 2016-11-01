#include "Grunt.h"

Grunt::Grunt(Ogre::SceneNode * GruntNode, Ogre::AnimationState * move, Ogre::AnimationState * attack, Ogre::AnimationState * die)
{
    _name = "Grunt";
    _maxHp = 300;
    _hp = 300;
    _speed = 5;
    _damage = 30;
    _range = 2;
    _node = GruntNode;
    _animations["move"] = move;
    _animations["attack"] = attack;
    _animations["die"] = die;
    _range = 5;
    gui = 0;
    _attack = CAC;
    _isHero = false;
}

Grunt::~Grunt()
{
}

Ogre::AnimationState * Grunt::attack()
{
    return _animations["attack"];
}

Ogre::AnimationState * Grunt::move(const Ogre::Vector3 & pos)
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

Ogre::AnimationState * Grunt::die()
{
    return _animations["die"];
}
