#include "Entities/ACharacter.h"
#include "DamagePowerUp.h"

DamagePowerUp::DamagePowerUp(Ogre::SceneNode *nnode)
{
  node = nnode;
  delay = DAMAGE_TIME;
}

DamagePowerUp::~DamagePowerUp()
{
}

void	DamagePowerUp::onTake(ACharacter *character, irrklang::ISoundEngine *engine)
{
  this->character = character;
  engine->play2D("../sound/sword.wav");
  std::cout << "J'augmente les damages" << std::endl;
  character->setDamage(character->getDamage() * DAMAGE_VALUE);
  timer.startTime();
}

void	DamagePowerUp::finishEffect() const
{
  std::cout << "Les damages redeviennent normaux" << std::endl;
  character->setDamage(character->getDamage() / DAMAGE_VALUE);
}
