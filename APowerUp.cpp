#include "Entities/ACharacter.h"
#include "AItem.h"

APowerUp::APowerUp()
{
}

APowerUp::~APowerUp()
{
}

void APowerUp::onTake(ACharacter *character, irrklang::ISoundEngine *engine)
{
}

bool    APowerUp::checkIfActive()
{
  if (timer.getTimeElapsedSec() >= delay)
    return (false);
  return (true);
}
