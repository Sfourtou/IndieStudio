#include "Entities/ACharacter.h"
#include "Potion.h"

Potion::Potion(Ogre::SceneNode *nnode)
{
  node = nnode;
}

Potion::~Potion()
{
}

void	Potion::onTake(ACharacter *character, irrklang::ISoundEngine *engine)
{
  std::cout << "Je heal le mec" << std::endl;
  engine->play2D("../sound/potion.wav");
  character->setHp(character->getHp() + HEAL_VALUE);
}
