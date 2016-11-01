#include "Camera.h"

Camera::Camera(Ogre::Camera *&camera)
: mCamera(camera), x(0), y(100), z(50), lookAtX(0), lookAtY(-200), lookAtZ(-300)
{

}

void Camera::setPositon(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
    mCamera->setPosition(x, y, z);
}

void Camera::lookAt(int x, int y, int z)
{
    lookAtX = x;
    lookAtY = y;
    lookAtZ = z;
    mCamera->lookAt(x, y, z);
}

int     Camera::getPositionX()
{
    return (this->x);
}

int     Camera::getPositionY()
{
    return (this->y);
}

int     Camera::getPositionZ()
{
    return (this->z);
}

int     Camera::getLookAtX()
{
    return (this->lookAtX);
}

int     Camera::getLookAtY()
{
    return (this->lookAtY);
}

int     Camera::getLookAtZ()
{
    return (this->lookAtZ);
}
