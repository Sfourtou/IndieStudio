#include "Entities/ACharacter.h"
#include "Key.h"

Key::Key(Ogre::SceneNode *nnode)
{
  node = nnode;
}

Key::~Key()
{
}

void
Key::onTake(ACharacter *character, irrklang::ISoundEngine *engine)
{
  character->setKeyCount(character->getKeyCount() + 1);
}
