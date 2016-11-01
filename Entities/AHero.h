#ifndef AHERO_H_
# define AHERO_H_

#include "../Keyboard.h"

enum IAType
{
  COMPUTER,
  HUMAN
};

class AHero
{
public:
  AHero();
  ~AHero();
  void setType(IAType);
  IAType getType() const;
protected:
  IAType type;
};

#endif
