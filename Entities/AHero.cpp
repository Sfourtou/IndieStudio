#include "AHero.h"

AHero::AHero()
{
}

AHero::~AHero()
{
}

void
AHero::setType(IAType nt)
{
  type = nt;
}

IAType
AHero::getType() const
{
  return (type);
}







