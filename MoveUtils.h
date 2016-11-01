#ifndef GAUNTLET_MOVEUTILS_H
#define GAUNTLET_MOVEUTILS_H


#include <OgreVector3.h>
#include "CollisionTools.h"

class MoveUtils {
public:
    static Ogre::Real abs(Ogre::Real value);
    static bool isOnTarget(Ogre::Vector3 position, Ogre::Vector3 target, float precision);
    static bool canGoStraightAhead(MOC::CollisionTools *collision, Ogre::Vector3 position, Ogre::Vector3 target, float precision);
    static Ogre::Vector3 getDirection(Ogre::Vector3 postion, Ogre::Vector3 target);
};


#endif //GAUNTLET_MOVEUTILS_H
