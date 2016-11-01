#include "Zone.h"

Zone::Zone(int idZone, Ogre::Vector3 start, Ogre::Vector3 target)
: _idZone(idZone), _start(start), _target(target), _exitIsOpen(false), _enterIsOpen(false), _idxWay(0), _state(ZoneState::START)
{
    if (_idZone == 1) {
        _way.push_back(Ogre::Vector3(-213, -88, 49));
        _way.push_back(Ogre::Vector3(-231, -88, 17));
        _way.push_back(Ogre::Vector3(-267, -88, -40));
        _way.push_back(Ogre::Vector3(-268, -88, -85));
        _way.push_back(Ogre::Vector3(-253, -88, -106));
        _way.push_back(Ogre::Vector3(-230, -88, -124));
    }
    if (_idZone == 2)
    {
        _way.push_back(Ogre::Vector3(-100, -88, -208));
        _way.push_back(Ogre::Vector3(-59, -88, -206));
        _way.push_back(Ogre::Vector3(0, -88, -182));
        _way.push_back(Ogre::Vector3(81, -88, -182));
    }
    if (_idZone == 3)
    {
        _way.push_back(Ogre::Vector3(130, -88, -133));
        _way.push_back(Ogre::Vector3(131, -88, -104));
        _way.push_back(Ogre::Vector3(134, -88, -97));
        _way.push_back(Ogre::Vector3(184, -88, -36));
        _way.push_back(Ogre::Vector3(190, -88, -30));
        _way.push_back(Ogre::Vector3(197, -88, 1));
        _way.push_back(Ogre::Vector3(195, -88, 61));
        _way.push_back(Ogre::Vector3(178, -88, 95));
        //_way.push_back(Ogre::Vector3(165, -88, 109));
        _way.push_back(Ogre::Vector3(176, -88, 102));
        _way.push_back(Ogre::Vector3(171, -88, 106));
    }
    if (_idZone == 4)
    {
        _way.push_back(Ogre::Vector3(106, -88, 101));
        _way.push_back(Ogre::Vector3(75, -88, 80));
        _way.push_back(Ogre::Vector3(31, -88, 78));
        _way.push_back(Ogre::Vector3(0, -88, 69));
        _way.push_back(Ogre::Vector3(-4, -88, 51));
        _way.push_back(Ogre::Vector3(-6, -88, 36));
        _way.push_back(Ogre::Vector3(-6, -88, 19));
        _way.push_back(Ogre::Vector3(-8, -88, 11));
    }
    if (_idZone == 5)
    {
        _way.push_back(Ogre::Vector3(-44, -88, -80));
        _way.push_back(Ogre::Vector3(-47, -88, -93));
        _way.push_back(Ogre::Vector3(-47, -88, -100));
        _way.push_back(Ogre::Vector3(-51, -88, -114));
        _way.push_back(Ogre::Vector3(-55, -88, -132));
    }
}

int Zone::getId() const
{
    return _idZone;
}

Ogre::Vector3   Zone::getStartZonePosition() const
{
    return _start;
}

Ogre::Vector3   Zone::getTargetPosition() const
{
    return _target;
}

ZoneState Zone::getState() const {
    return _state;
}

void Zone::setState(ZoneState state) {
    _state = state;
}

Ogre::Vector3   Zone::getPosition()
{
    if (_idxWay >= _way.size())
        return (Ogre::Vector3::ZERO);
    return _way[_idxWay];
}

Ogre::Vector3   Zone::getNextPosition()
{
    if (_idxWay >= _way.size())
        return (Ogre::Vector3::ZERO);
    return _way[++_idxWay];
}

Ogre::AnimationState *Zone::getEnterAnimation() const {
    return _enter;
}

Ogre::AnimationState *Zone::getExitAnimation() const {
    return _exit;
}

void Zone::setEnterAnimation(Ogre::AnimationState *enter) {
    _enter = enter;

}

void Zone::setExitAnimation(Ogre::AnimationState *exit) {
    _exit = exit;
}

bool Zone::enterIsOpen() const {
    return _enterIsOpen;
}

void Zone::setEnterIsOpen(bool isOpen) {
    _enterIsOpen = isOpen;
}

bool Zone::exitIsOpen() const {
    return _exitIsOpen;
}

void Zone::setExitIsOpen(bool isOpen) {
    _exitIsOpen = isOpen;
}
