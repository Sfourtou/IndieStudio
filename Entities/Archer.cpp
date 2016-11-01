#include "Archer.h"

Archer::Archer(Ogre::SceneNode * archerNode, Ogre::AnimationState * move, Ogre::AnimationState * attack, Ogre::AnimationState * die, IAType t)
{
    _name = "Archer";
    _maxHp = 500;
    _hp = 500;
    _keyCount = 0;
    _speed = 15;
    _damage = 60;
    _node = archerNode;
    _animations["move"] = move;
    _animations["attack"] = attack;
    _animations["die"] = die;
    type = t;
    _range = 40;
    gui = 0;
    _attack = RANGE;
    _isHero = true;
}

Archer::~Archer()
{

}

Ogre::AnimationState * Archer::attack(){
    if (_animations["move"]->getEnabled())
        _animations["move"]->setEnabled(false);
    return _animations["attack"];
}

Ogre::AnimationState * Archer::move(const Ogre::Vector3 &pos){

    if (pos.x == 0 && pos.y == 0 && pos.z == 0)
        return (0);
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

Ogre::AnimationState * Archer::die(){
    return _animations["die"];
}
