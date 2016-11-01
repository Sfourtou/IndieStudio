#include "MoveUtils.h"

bool MoveUtils::isOnTarget(Ogre::Vector3 position, Ogre::Vector3 target, float precision) {
    return (abs((int) sqrt(pow(target.x - position.x, 2) + pow(target.z - position.z, 2)))) <= precision;
}

bool MoveUtils::canGoStraightAhead(MOC::CollisionTools *collision, Ogre::Vector3 position, Ogre::Vector3 target,
                                   float precision) {
    float dist = 0;
    return (!collision->collidesWithEntity(position, target, dist, precision, 1.0f));
}

Ogre::Vector3 MoveUtils::getDirection(Ogre::Vector3 position, Ogre::Vector3 target) {
    Ogre::Vector3 sens = target - position;
    Ogre::Vector3 sens2(sens.x / (MoveUtils::abs(sens.x) + MoveUtils::abs(sens.z)), 0, sens.z / (MoveUtils::abs(sens.x) + MoveUtils::abs(sens.z)));
    return sens2;
}

Ogre::Real MoveUtils::abs(Ogre::Real value) {
    return (value < 0 ? -value : value);
}
