#include "Warrior.h"
#include "AHero.h"

Warrior::Warrior(Ogre::SceneNode * WarriorNode, Ogre::AnimationState * move, Ogre::AnimationState * attack, Ogre::AnimationState * die, IAType t)
{
    _name = "Warrior";
    _maxHp = 1000;
    _hp = 1000;
    _keyCount = 0;
    _speed = 13;
    _damage = 80;
    _node = WarriorNode;
    _animations["move"] = move;
    _animations["attack"] = attack;
    _animations["die"] = die;
    type = t;
    _range = 7;
    gui = 0;
    _attack = CAC;
    _isHero = true;
}

Warrior::~Warrior()
{

}

Ogre::AnimationState * Warrior::attack(){
    return _animations["attack"];
}

Ogre::AnimationState * Warrior::move(const Ogre::Vector3 &pos){

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

Ogre::AnimationState * Warrior::die(){
    return _animations["die"];
}
