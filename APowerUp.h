#ifndef APOWERUP_H_
# define APOWERUP_H_
# include <OGRE/OgreSceneNode.h>
# include "AItem.h"
# include "Timer.h"

class APowerUp : public AItem
{
 public:
  APowerUp();
  ~APowerUp();
  virtual void onTake(ACharacter *character, irrklang::ISoundEngine *engine);
  virtual bool checkIfActive();
  virtual void finishEffect() const = 0;
 protected:
  ACharacter *character;
  Timer timer;
  int delay;
};

#endif
