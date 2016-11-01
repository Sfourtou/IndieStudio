#ifndef KEY_H_
# define KEY_H_

class Key : public AItem
{
public:
  Key(Ogre::SceneNode *node);
  ~Key();
  void onTake(ACharacter *character, irrklang::ISoundEngine *engine);
};

#endif
