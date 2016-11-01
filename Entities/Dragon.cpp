#include "Dragon.h"

Dragon::Dragon(Ogre::SceneNode *node, Ogre::AnimationState * intro, Ogre::AnimationState * attack1, Ogre::AnimationState * attack2, Ogre::AnimationState * attack3, Ogre::AnimationState * die) {
    _name = "DRAGON !!!";
    _hp = 1500;
    _maxHp = 1500;
    _keyCount = 0;
    _speed = 7;
    _damage = 100;
    _range = 60;
    _node = node;
    _animations["intro"] = intro;
    _animations["attack1"] = attack1;
    _animations["attack2"] = attack2;
    _animations["attack3"] = attack3;
    _animations["die"] = die;
    gui = 0;
    _attack = BOSS;
    _isHero = false;
    _isDead = false;
}

Dragon::~Dragon() {

}

Ogre::AnimationState * Dragon::move(__attribute__((unused)) const Ogre::Vector3 &pos){
    return NULL;
}

Ogre::AnimationState * Dragon::attack(){
    if (_hp > 999)
        return (_animations["attack2"]);
    else if (_hp > 500 && _hp < 1000)
        return (_animations["attack2"]);
    return (_animations["attack3"]);
}

Ogre::AnimationState * Dragon::die(){
    return _animations["die"];
}

Ogre::AnimationState * Dragon::intro(){
    return _animations["intro"];
}

Projectile * Dragon::attack(Ogre::SceneManager *sceneMgr) {
    Ogre::Entity *entity;

    entity = sceneMgr->createEntity(std::string("Sphere.mesh"));
    Ogre::SceneNode *node = sceneMgr->getRootSceneNode()->createChildSceneNode(getPosition() + Ogre::Vector3(0, 3, 0) + Ogre::Vector3::UNIT_Y);
    node->scale(4, 4, 4);
    node->attachObject(entity);
    return (new Projectile(this, node, entity->getAnimationState("rotate"), getRange()));
}

Projectile * Dragon::threeProjectiles(Ogre::SceneManager * sceneMgr, const Ogre::Vector3 & pos){
    Ogre::Entity *entity;

    entity = sceneMgr->createEntity(std::string("Sphere.mesh"));
    Ogre::SceneNode *node = sceneMgr->getRootSceneNode()->createChildSceneNode(getPosition() + Ogre::Vector3(0, 3, 0) + Ogre::Vector3::UNIT_Y);
    node->attachObject(entity);
    node->scale(2, 2, 2);
    return (new Projectile(this, node, entity->getAnimationState("rotate"), getRange(), pos));
}

AItem *
Dragon::onDie(Ogre::SceneManager *scene) const {
    Ogre::SceneNode *node;
    Ogre::Entity *e;
    Ogre::Vector3 pos;
    Key *key;

    e = scene->createEntity("Key.mesh");
    pos = _node->getPosition();
    node = scene->getRootSceneNode()->createChildSceneNode(pos);
    node->attachObject(e);
    node->setScale(0.5, 0.5, 0.5);
    key = new Key(node);
    key->setAnim(e->getAnimationState("rotate"));
    return (key);
}

void Dragon::setDead()
{
    _isDead = true;
}

bool Dragon::isDead() const
{
    return _isDead;
}
