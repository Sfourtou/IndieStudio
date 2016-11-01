#ifndef SPEEDPOWERUP_H_
# define SPEEDPOWERUP_H_
# define SPEED_VALUE 1.5
# define SPEED_TIME 5
# include "APowerUp.h"

class SpeedPowerUp : public APowerUp
{
 public:
  SpeedPowerUp(Ogre::SceneNode *node);
  ~SpeedPowerUp();
  void onTake(ACharacter *character, irrklang::ISoundEngine *engine);
  void finishEffect() const;
};

#endif
