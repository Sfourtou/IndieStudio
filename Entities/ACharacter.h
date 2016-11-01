#ifndef GAUNTLET_ACHARACTER_H
#define GAUNTLET_ACHARACTER_H

#define KEY_PROB 10
#define POT_PROB 10
#define SPD_PROB 10
#define DMG_PROB 10

#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>
#include <string>
#include <vector>
#include "../Menu.hh"
#include "../AItem.h"
#include "../Key.h"
#include "../Potion.h"
#include "../SpeedPowerUp.h"
#include "../DamagePowerUp.h"
#include "../Keyboard.h"
#include "../Projectile.h"

enum attackType{
    CAC,
    RANGE,
    EXPLODE,
    BOSS
};

class ACharacter {
public:
    ACharacter();
    virtual ~ACharacter();
protected:
    int _maxHp;
    int _hp;
    float _speed;
    float _range;
    int _damage;
    int _keyCount;
    bool _isHero;
    std::string _name;
    Ogre::SceneNode * _node;
    std::map<std::string, Ogre::AnimationState *> _animations;
    Ogre::Vector3 _dir;
    Ogre::Vector3 _lastDir;
    guiHero       *gui;
    Keyboard    *_key;
    int         nbProjectile;
    bool        _isAttacking;
    int         _currentZone;
    attackType  _attack;
    long        _time;
public:
    int getHp();
    float getSpeed();
    int getDamage();
    int getKeyCount() const;
    int getMaxHp() const;
    attackType getAttackType() const;
    guiHero     *getGui() const;
    Ogre::Vector3 const &getPosition() const;
    std::string getName();
    Ogre::Entity * getEntity();
    Ogre::SceneNode * getNode();
    void setHp(int hp);
    void setSpeed(float speed);
    void setDamage(int damage);
    void setName(const std::string & name);
    void setKeyCount(int);
    void setGui(guiHero *hero);
    virtual Ogre::AnimationState * move(const Ogre::Vector3 &) = 0;
    virtual Ogre::AnimationState * attack() = 0;
    virtual Ogre::AnimationState * die() = 0;
    virtual AItem *onDie(Ogre::SceneManager *scene) const;
    Keyboard *const &getKey() const;
    void setKey(Keyboard *key);
    void setNbProjectile(int value);
    int  getNbProjectile() const;
    Ogre::Vector3 getDir() const;
    void setDir(Ogre::Vector3 dir);
    Ogre::Vector3 const &getLastDir() const;
    void setLastDir(Ogre::Vector3 dir);
    float getRange() const;
    void setRange(float range);
    void setIsAttacking(bool attack);
    bool isAttacking() const;
    virtual Projectile  *attack(Ogre::SceneManager *);
    void setCurrentZone(int zone);
    bool isHero();
    int getCurrentZone() const;
};


#endif //GAUNTLET_ACHARACTER_H
