#ifndef DAMAGEPOWERUP_H_
# define DAMAGEPOWERUP_H_
# define DAMAGE_VALUE 1.5
# define DAMAGE_TIME 5
# include "APowerUp.h"
# include "Timer.h"

class DamagePowerUp : public APowerUp
{
 public:
  DamagePowerUp(Ogre::SceneNode *node);
  ~DamagePowerUp();
  void onTake(ACharacter *character, irrklang::ISoundEngine *engine);
  void finishEffect() const;
};

#endif
