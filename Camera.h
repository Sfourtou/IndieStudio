#ifndef GAUNTLET_CAMERA_H
#define GAUNTLET_CAMERA_H


#include <OGRE/Ogre.h>

class Camera {
private:
    Ogre::Camera    *mCamera;
    int             x;
    int             y;
    int             z;
    int             lookAtX;
    int             lookAtY;
    int             lookAtZ;
public:
    Camera(Ogre::Camera * &camera);
    void setPositon(int x, int y, int z);

    void lookAt(int x, int y, int z);

    int getPositionZ();

    int getPositionY();

    int getPositionX();

    int getLookAtX();

    int getLookAtY();

    int getLookAtZ();
};


#endif //GAUNTLET_CAMERA_H
