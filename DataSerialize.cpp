#include "DataSerialize.h"

DataSerialize::DataSerialize()
{
}

DataSerialize::~DataSerialize()
{
}

std::string heroName;

Spawner *
DataSerialize::createSpawner(Spawner *spawner, int hp, int zone) const
{
  spawner->setHp(hp);
  spawner->setCurrentZone(zone);
  return (spawner);
}

ACharacter *
DataSerialize::createCharacter(const float *tab, EntitiesFactory *ef, Ogre::SceneManager *scene, int &heroCount, Keyboard *player1, Keyboard *player2) const
{
  Ogre::Vector3 pos(tab[0], tab[1], tab[2]);
  ACharacter *character;

  if (tab[3] == LUTIN)
  {
    character = ef->createArcher(scene, pos, (IAType)tab[5]);
    if ((IAType)tab[5] == HUMAN && heroCount == 0)
    {
      character->setKey(player1);
      ++heroCount;
    }
    else if ((IAType)tab[5] == HUMAN && heroCount == 1)
    {
      character->setKey(player2);
      ++heroCount;
    }
    if ((IAType)tab[5] == HUMAN)
    {
      character->setName(heroName);
    }
    return (character);
  }
  if (tab[3] == GHOST)
    return (ef->createGhost(scene, pos));
  if (tab[3] == GRUNT)
    return (ef->createGrunt(scene, pos));
  if (tab[3] == DEMON)
    return (ef->createSorcerer(scene, pos));
  if (tab[3] == WARRIOR)
  {
    character = ef->createWarrior(scene, pos, (IAType)tab[5]);
    if ((IAType)tab[5] == HUMAN && heroCount == 0)
    {
      character->setKey(player1);
      ++heroCount;
    }
    else if ((IAType)tab[5] == HUMAN && heroCount == 1)
    {
      character->setKey(player2);
      ++heroCount;
    }
    if ((IAType)tab[5] == HUMAN)
      character->setName(heroName);
    return (character);
  }
  return (0);
}

AItem *
DataSerialize::createDrop(const float *tab, EntitiesFactory *ef, Ogre::SceneManager *scene) const
{
  Ogre::Vector3 pos(tab[0], tab[1], tab[2]);

  if (tab[3] == POTION)
    return (ef->createPotion(scene, pos));
  if (tab[3] == KEY)
    return (ef->createKey(scene, pos));
  if (tab[3] == SPEEDPOWERUP)
    return (ef->createSpeedPowerUp(scene, pos));
  if (tab[3] == DAMAGEPOWERUP)
    return (ef->createDamagePowerUp(scene, pos));
  return (0);
}

IAType
DataSerialize::getIAType(ACharacter *character)
{
  AHero     *hero;

  if ((hero = dynamic_cast<AHero *>(character)))
    return (hero->getType());
  return (HUMAN);
}

CharacterType
DataSerialize::getType(ACharacter *character)
{
  if (dynamic_cast<Archer *>(character))
    return (LUTIN);
  if (dynamic_cast<Ghost *>(character))
    return (GHOST);
  if (dynamic_cast<Grunt *>(character))
    return (GRUNT);
  if (dynamic_cast<Warrior *>(character))
    return (WARRIOR);
  if (dynamic_cast<Demon *>(character))
    return (DEMON);
  return (CHARA_UNDEFINED);
}

DropType
DataSerialize::getType(AItem *item)
{
  if (dynamic_cast<Potion *>(item))
    return (POTION);
  if (dynamic_cast<Key *>(item))
    return (KEY);
  if (dynamic_cast<SpeedPowerUp *>(item))
    return (SPEEDPOWERUP);
  if (dynamic_cast<DamagePowerUp *>(item))
    return (DAMAGEPOWERUP);
  return (DROP_UNDEFINED);
}

void save(const std::vector<ACharacter *> ennemies, const std::vector<ACharacter *> heros, const std::vector<AItem *> drops, const std::vector<Spawner *> spawners, const std::vector<Projectile *> projectile, int score, const std::vector<Zone *>zones, int doorsNumber)
{
  DIR           *dp;
  int           length = 0;
  struct dirent *ep;
  int           state;

  dp = opendir(SAVES_PATH);
  if (dp != NULL)
  {
    while (ep = readdir(dp))
      ++length;
    closedir(dp);
  }
  std::ofstream s (std::string(SAVES_PATH) + std::string(GAME_NAME) + std::to_string(length), std::ofstream::out);
  s << ENNEMIES << std::endl;
  for (auto it = ennemies.begin(); it != ennemies.end(); ++it)
  {
    const Ogre::Vector3 pos = (*it)->getPosition();
    s << pos.x << " " << pos.y << " " << pos.z << " " << DataSerialize::getType(*it) << " " << (*it)->getCurrentZone() << std::endl;
  }

  s << HEROS << std::endl;
  for (auto it = heros.begin(); it != heros.end(); ++it)
  {
    const Ogre::Vector3 pos = (*it)->getPosition();
    if ((*it)->getCurrentZone() >= zones.size())
      state = 0;
    else
      state = zones[(*it)->getCurrentZone()]->getState();
    s << pos.x << " " << pos.y << " " << pos.z << " " << DataSerialize::getType(*it) << " " << (*it)->getHp() << " " << DataSerialize::getIAType(*it) << " " << (*it)->getCurrentZone() << " " << (*it)->getKeyCount() << " " << state << " " << (*it)->getName() << std::endl;
  }

  s << DROPS << std::endl;
  for (auto it = drops.begin(); it != drops.end(); ++it)
  {
    Ogre::Vector3 pos = (*it)->getNode()->getPosition();
    s << pos.x << " " << pos.y << " " << pos.z << " " << DataSerialize::getType(*it) << std::endl;
  }

  s << SPAWNERS << std::endl;
  for (auto it = spawners.begin(); it != spawners.end(); ++it)
  {
    const float *tab = (*it)->getPos();
    s << tab[0] << " " << tab[1] << " " << tab[2] << " " << (*it)->getHp() << " " << (*it)->getCurrentZone() << std::endl;
  }
  s << T_SCORE << std::endl << score << std::endl << DOORS << std::endl << doorsNumber << std::endl << END << std::endl;
  s.close();
}

void
DataSerialize::saveGame(const std::vector<ACharacter *> ennemies, const std::vector<ACharacter *> heros, const std::vector<AItem *> drops, const std::vector<Spawner *> spawners, const std::vector<Projectile *> projectile, int score, const std::vector<Zone *> zones, int doors)
{
  std::thread(save, ennemies, heros, drops, spawners, projectile, score, zones, doors).detach();
}

void
DataSerialize::loadGame(Game *game, std::string const &name, EntitiesFactory *ef, Ogre::SceneManager *sceneMgr, Menu *menu, Keyboard *player1, Keyboard *player2)
{
  std::ifstream s(SAVES_PATH + name, std::ifstream::in);
  std::string buff;
  // 0 -> ennemies
  // 1 -> heros
  // 2 -> drops
  // 3 -> spawners
  // 4 -> score
  // 5 -> doors
  int opt = -1;
  int i;
  int lim;
  int heroCount = 0;
  float tab[9] = {0, 0, 0, 0, 0, 0, 0, 0};
  bool hasShifted = false;
  Ogre::Vector3 pos;

  s >> buff;
  while (buff != END)
  {
    hasShifted = false;
    if (buff == ENNEMIES)
    {
      lim = 5;
      opt = 0;
    }
    else if (buff == HEROS)
    {
      lim = 10;
      opt = 1;
    }
    else if (buff == DROPS)
    {
      lim = 4;
      opt = 2;
    }
    else if (buff == SPAWNERS)
    {
      lim = 5;
      opt = 3;
    }
    else if (buff == T_SCORE)
    {
      lim = 1;
      opt = 4;
    }
    else if (buff == DOORS)
    {
      lim = 1;
      opt = 5;
    }
    else
      {
        hasShifted = true;
        i = -1;
        while (++i < lim)
        {
          if (i == 9)
            heroName = buff;
          else
            tab[i] = std::stod(buff);
          s >> buff;
        }
       if (opt == 0)
         game->addEnnemy(createCharacter(tab, ef,sceneMgr, heroCount, player1, player2), (int)tab[4]);
         else if (opt == 1)
          game->addHero(createCharacter(tab, ef, sceneMgr, heroCount, player1, player2), (IAType)tab[5], menu, (int)tab[4], (int)tab[6], (int)tab[7], (int)tab[8]);
        else if (opt == 2)
          game->addDrop(createDrop(tab, ef, sceneMgr));
        else if (opt == 3)
          {
            pos.x = tab[0];
            pos.y = tab[1];
            pos.z = tab[2];
            game->addSpawner(createSpawner(ef->createSpawner(sceneMgr, pos), (int)tab[3], (int)tab[4]));
          }
        else if (opt == 4)
          game->setScore(tab[0]);
        else if (opt == 5)
          game->setIdx((int)tab[0], sceneMgr);
      }
      if (!hasShifted)
        s >> buff;
  }
}
