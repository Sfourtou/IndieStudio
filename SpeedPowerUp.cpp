#include "Entities/ACharacter.h"
#include "SpeedPowerUp.h"

SpeedPowerUp::SpeedPowerUp(Ogre::SceneNode *nnode)
{
  node = nnode;
  delay = SPEED_TIME;
}

SpeedPowerUp::~SpeedPowerUp()
{
}

void	SpeedPowerUp::onTake(ACharacter *character, irrklang::ISoundEngine *engine)
{
  this->character = character;
  std::cout << "J'augmente la speed" << std::endl;
  character->setSpeed(character->getSpeed() * SPEED_VALUE);
  timer.startTime();
}

void	SpeedPowerUp::finishEffect() const
{
  std::cout << "La speed redevient normale" << std::endl;
  character->setSpeed(character->getSpeed() / SPEED_VALUE);
}
