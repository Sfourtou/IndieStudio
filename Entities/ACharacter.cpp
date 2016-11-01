#include "ACharacter.h"
#include "../Keyboard.h"

ACharacter::ACharacter()
: _key(NULL), _dir(Ogre::Vector3::ZERO), _lastDir(Ogre::Vector3::UNIT_Z), nbProjectile(0), _isAttacking(false), _currentZone(0)
{
    _time = 0;
    _isHero = false;
}

ACharacter::~ACharacter()
{}

int ACharacter::getHp() {
    return _hp;
}

int ACharacter::getMaxHp() const {
    return _maxHp;
}

float ACharacter::getSpeed() {
    return _speed;
}

int ACharacter::getDamage(){
    return _damage;
}

std::string ACharacter::getName(){
    return _name;
}

Ogre::Entity * ACharacter::getEntity() {
    return NULL;
}

Ogre::SceneNode * ACharacter::getNode(){
    return _node;
}

void ACharacter::setHp(int hp) {
    if ((_hp = hp) > _maxHp)
      _hp = _maxHp;
    if (_hp < 0)
      _hp = 0;
    if (gui)
      gui->bar->setProgress((float)_hp / (float)_maxHp);
}

void ACharacter::setName(const std::string & name){
    _name = name;
}

void ACharacter::setDamage(int damage){
    _damage = damage;
}

void ACharacter::setSpeed(float speed){
    _speed = speed;
}

Ogre::Vector3 const &ACharacter::getPosition() const {
    return _node->getPosition();
}

AItem *
ACharacter::onDie(Ogre::SceneManager *scene) const
{
  int pot;
  int spd;
  int dmg;
  Ogre::SceneNode *node;
  Ogre::Entity *e;
  Ogre::Vector3 pos;
    AItem * myItem;

  pot = rand() % 100;
  spd = rand() % 100;
  dmg = rand() % 100;
  pos = _node->getPosition();
  if (pot <= POT_PROB)
    {
      e = scene->createEntity("LifePotion.mesh");
      node = scene->getRootSceneNode()->createChildSceneNode(pos);
      node->attachObject(e);
      node->setScale(0.5, 0.5, 0.5);
      myItem = new Potion(node);
        myItem->setAnim(e->getAnimationState("rotate"));
        return (myItem);
    }
  if (spd <= SPD_PROB)
    {
      e = scene->createEntity("Claquette.mesh");
      node = scene->getRootSceneNode()->createChildSceneNode(pos);
      node->attachObject(e);
      node->setScale(10, 10, 10);
        myItem = new SpeedPowerUp(node);
        myItem->setAnim(e->getAnimationState("rotate"));
      return (myItem);
    }
  if (dmg <= DMG_PROB)
    {
      e = scene->createEntity("Sword.mesh");
      node = scene->getRootSceneNode()->createChildSceneNode(pos);
      node->attachObject(e);
      node->setScale(1, 1, 1);
        myItem = new DamagePowerUp(node);
        myItem->setAnim(e->getAnimationState("rotate"));
      return (myItem);
    }
  return (0);
}

int
ACharacter::getKeyCount() const
{
  return (_keyCount);
}

void
ACharacter::setKeyCount(int k)
{
  _keyCount = k;
}

void
ACharacter::setGui(guiHero *hero)
{
  gui = hero;
}

guiHero *
ACharacter::getGui() const
{
    return (gui);
}

Keyboard *const &ACharacter::getKey() const {
    return _key;
}

void ACharacter::setKey(Keyboard *key) {
    _key = key;
}

Ogre::Vector3 ACharacter::getDir() const {
    return _dir;
}

void ACharacter::setDir(Ogre::Vector3 dir) {
    _dir = dir;
}

Ogre::Vector3 const &ACharacter::getLastDir() const {
    return _lastDir;
}

void ACharacter::setLastDir(Ogre::Vector3 dir) {
    _lastDir = dir;
}

float ACharacter::getRange() const {
    return _range;
}

void ACharacter::setRange(float range) {
    _range = range;
}

Projectile *ACharacter::attack(Ogre::SceneManager *sceneMgr) {
    Ogre::Entity *entity;

    entity = sceneMgr->createEntity(isHero() ? std::string("Shuriken.mesh") : std::string("Sphere.mesh"));
    Ogre::SceneNode *node = sceneMgr->getRootSceneNode()->createChildSceneNode(getPosition() + Ogre::Vector3::UNIT_Y);
    node->attachObject(entity);
    if (isHero())
        node->scale(0.15, 0.15, 0.15);
    else
        node->scale(0.6, 0.6, 0.6);
    return (new Projectile(this, node, entity->getAnimationState("rotate"), getRange()));
}

void ACharacter::setNbProjectile(int value) {
    nbProjectile += value;
}

int ACharacter::getNbProjectile() const {
    return nbProjectile;
}

void ACharacter::setIsAttacking(bool attack) {
    _isAttacking = attack;
}

bool ACharacter::isAttacking() const {
    return _isAttacking;
}

void    ACharacter::setCurrentZone(int zone)
{
    _currentZone = zone;
}

int     ACharacter::getCurrentZone() const
{
    return _currentZone;
}

attackType ACharacter::getAttackType() const {
    return _attack;
}

bool ACharacter::isHero() {
    return _isHero;
}
