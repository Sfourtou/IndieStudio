#ifndef GAUNTLET_ZONE_H
#define GAUNTLET_ZONE_H


#include <OGRE/OgreVector3.h>

enum ZoneState
{
    START,
    COMBAT,
    TARGET,
    NEXTZONE,
};

class Zone {
public:
    Zone(int, Ogre::Vector3, Ogre::Vector3);
    ~Zone() {};

    Ogre::Vector3 getTargetPosition() const;

private:

    int             _idZone;
    Ogre::Vector3   _start;
    Ogre::Vector3   _target;
    std::vector<Ogre::Vector3> _way;
    bool            _enterIsOpen;
    bool            _exitIsOpen;
    int             _idxWay;
    ZoneState       _state;
    Ogre::AnimationState *_enter;
    Ogre::AnimationState *_exit;

public:
    int getId() const;

    Ogre::Vector3 getStartZonePosition() const;

    bool enterIsOpen() const;

    void setEnterIsOpen(bool isOpen);

    bool exitIsOpen() const;

    void setExitIsOpen(bool isOpen);

    Ogre::Vector3 getNextPosition();

    ZoneState   getState() const;
    void        setState(ZoneState state);

    Ogre::Vector3 getPosition();

    Ogre::AnimationState *getEnterAnimation() const;
    Ogre::AnimationState *getExitAnimation() const;
    void    setEnterAnimation(Ogre::AnimationState *);
    void    setExitAnimation(Ogre::AnimationState *);

};


#endif //GAUNTLET_ZONE_H
