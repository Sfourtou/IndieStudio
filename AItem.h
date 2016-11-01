#ifndef AITEM_H_
# define AITEM_H_
# include <OGRE/OgreSceneNode.h>
# include "sound/include/irrKlang.h"

class ACharacter;

class AItem
{
public:
     AItem();
    ~AItem();
    virtual void onTake(ACharacter *character, irrklang::ISoundEngine *engine) = 0;
    Ogre::SceneNode *getNode() const;
    Ogre::AnimationState * getAnim() const;
    void setAnim(Ogre::AnimationState * myAnim);
protected:
  Ogre::SceneNode *node;
  Ogre::AnimationState * anim;
};

#endif
