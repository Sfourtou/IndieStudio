#include "Entities/ACharacter.h"
#include "AItem.h"

AItem::AItem()
{
}

AItem::~AItem()
{
}

Ogre::SceneNode *
AItem::getNode() const
{
  return (node);
}

Ogre::AnimationState *AItem::getAnim() const {
  return anim;
}

void AItem::setAnim(Ogre::AnimationState *myAnim) {
  anim = myAnim;
}




