#ifndef POTION_H_
# define POTION_H_
# define HEAL_VALUE 100

class Potion : public AItem
{
public:
  Potion(Ogre::SceneNode *node);
  ~Potion();
  void onTake(ACharacter *character, irrklang::ISoundEngine *engine);
};

#endif
