#ifndef DATA_SERIALIZE_H_
# define DATA_SERIALIZE_H_
# include <thread>
# include <vector>
# include <fstream>
# include <sys/types.h>
# include <dirent.h>
# include "Entities/ACharacter.h"
# include "Entities/EntitiesFactory.h"
# include "Entities/Spawner.h"
# include "Entities/Warrior.h"
# include "Entities/Archer.h"
# include "Entities/Demon.h"
# include "Projectile.h"
# include "Game.h"
# include "Menu.hh"
# define ENNEMIES "[ennemies]"
# define HEROS "[heros]"
# define DROPS "[drops]"
# define SPAWNERS "[spawners]"
# define PROJECTILES "[projectiles]"
# define T_SCORE "[score]"
# define DOORS "[doors]"
# define SAVES_PATH "../saves/"
# define GAME_NAME "game"
# define END "[END]"

class DataSerialize
{
public:
  DataSerialize();
  ~DataSerialize();
  void saveGame(const std::vector<ACharacter *> ennemies, const std::vector<ACharacter *> heros, const std::vector<AItem *> drops, const std::vector<Spawner *> spawners, const std::vector<Projectile *> projectile, int score, const std::vector<Zone *> zones, int doorsNumber);
  void loadGame(Game *game, std::string const &name, EntitiesFactory *ef, Ogre::SceneManager *sceneMgr, Menu *, Keyboard *player1, Keyboard *player2);
  static CharacterType getType(ACharacter *);
  static DropType      getType(AItem *);
  static IAType        getIAType(ACharacter *);
private:
  ACharacter *createCharacter(const float *, EntitiesFactory *ef, Ogre::SceneManager *scene, int &heroCount, Keyboard *, Keyboard *) const;
  Spawner   *createSpawner(Spawner *spawner, int hp, int zone) const;
  AItem *createDrop(const float *, EntitiesFactory *ef, Ogre::SceneManager *scene) const;
  ACharacter *findCharacter(float const *tab, EntitiesFactory *ef, Ogre::SceneManager *scene) const;
};

#endif
