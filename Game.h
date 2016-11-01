#ifndef GAME_H_
# define GAME_H_
# include <OGRE/Ogre.h>
# include <OIS/OIS.h>
# include <vector>
# include "CollisionTools.h"
# include "Entities/ACharacter.h"
# include "Entities/AHero.h"
# include "AItem.h"
# include "Projectile.h"
# include "Entities/Spawner.h"
# include "Scene.h"
# include "Menu.hh"
# include "Entities/EntitiesFactory.h"
# include "Zone.h"
# include "Entities/Archer.h"
# include "Entities/Ghost.h"
# include "Entities/Grunt.h"
# include "sound/include/irrKlang.h"
# include "sound/conio.h"
# include "Entities/Dragon.h"

# define CHEST_X -51
# define CHEST_Z -130
# define MARGIN -3

enum CharacterType
{
  CHARA_UNDEFINED,
  LUTIN,
  GHOST,
  DEMON,
  GRUNT,
  WARRIOR
};

# define START_POSITION Ogre::Vector3(-225, -88, 144)
//# define START_POSITION Ogre::Vector3(-16, -88, -45)
# define BOSS_POSITION Ogre::Vector3(-10, -87   , -30)
# define ADD_KILL 5
# define KILL_DRAGON 1000
Ogre::Real abs(Ogre::Real);

enum DropType
{
  DROP_UNDEFINED,
  POTION,
  KEY,
  SPEEDPOWERUP,
  DAMAGEPOWERUP
};

class Game {
public:
    Game();

    ~Game();

    void spawnEnnemies(Ogre::SceneManager *scene, EntitiesFactory *ef, const Ogre::FrameEvent &event);

    std::vector<ACharacter *> const *getHeros() const;

    ACharacter *getHero(int) const;

    void addHero(ACharacter *hero, IAType type, Menu *menu);

    void addHero(ACharacter *hero, IAType type, Menu *menu, int hp);

    void addHero(ACharacter *hero, IAType type, Menu *menu, int hp, int zone, int keyNb, int zoneState);

    void addHero(std::string const &name, std::string const &heroClass, IAType type, EntitiesFactory *ef,
                 Ogre::SceneManager *, Keyboard *, Keyboard *, Menu *);

    void addSpawner(Spawner *);

    void addEnnemy(ACharacter *ennemy, int zone);

    void addProjectile(Projectile *p);

    void addDrop(AItem *item);

    void deleteHero(ACharacter *hero);

    bool moveHeros(MOC::CollisionTools *, const Ogre::FrameEvent &event, Ogre::SceneNode *camNode, int &globalKeyCount,
                   bool checkColl, Ogre::SceneManager *mMgr, Menu *menu);

    void moveProjectile(MOC::CollisionTools *collisionManager, Ogre::Real frame, Ogre::SceneManager *);

    void moveAi(MOC::CollisionTools *collisionTools, const Ogre::FrameEvent &event, Ogre::SceneManager *pManager,
                int &global);

    void launchProjectile(Ogre::SceneManager *sceneMgr, ACharacter *character);

    bool closeAttack(ACharacter *character, Ogre::SceneManager *manager);

    void moveEnemies(Ogre::SceneManager *pManager, MOC::CollisionTools *event, const Ogre::FrameEvent &frameEvent,
                     Ogre::SceneManager *mSceneMgr);

    void attack(Ogre::SceneManager *sceneMgr, const Ogre::FrameEvent &frameEvent);

    void moveObjects(const Ogre::FrameEvent &frameEvent);

    void openTheDoor(Ogre::SceneManager *pManager, ACharacter *pCharacter, int key);

    bool dragonIsAlive() const;
private:
    std::vector<Zone *> zones;

    bool checkCollision(MOC::CollisionTools *collisionManager, Projectile *&projectile, Ogre::SceneManager *&mSceneMgr);

public:
    std::string const &getOwner() const;

    void setOwner(std::string const &);

    void checkDrop(Ogre::SceneManager *, Menu *menu);

    int getScore() const;

    void loadEverything(Ogre::SceneManager *pManager) const;

    void setScore(int nscore);

    void initGame(Menu *menu, EntitiesFactory *ef, Ogre::SceneManager *scene, Keyboard *, Keyboard *);

    std::vector<ACharacter *> getEnnemies() const;

    int getEnnemiesInZone(int zone) const;

    std::vector<AItem *> getDrops() const;

    std::vector<Spawner *> getSpawners() const;

    std::vector<Projectile *> getProjectiles() const;

    std::vector<Zone *> getZones() const;

    void dropsLoop();

    int getHuman() const;

    void setDoors(int);

    int getDoorsLength() const;

    void addDoor(Ogre::SceneNode *node);

    bool checkEnd() const;

    void clearResources(Ogre::SceneManager *scene);

    void bossPattern(Ogre::SceneManager *mSceneMgr, Ogre::FrameEvent frameEvent);

    void bossTime(Ogre::SceneManager *pManager);

    bool bossIsEnabled() const;
    bool moveCamera() const;
    void setMoveCamera(bool);
    int getIdx() const;
    void setIdx(int, Ogre::SceneManager *);
    void setSceneManager(Ogre::SceneManager *);

    irrklang::ISoundEngine *engine;
private:
    std::vector<ACharacter *> ennemies;
    std::vector<ACharacter *> heros;
    std::vector<AItem *> drops;
    std::vector<Spawner *> spawners;
    std::vector<Projectile *> projectiles;
    std::vector<APowerUp *> powerUps;
    std::vector<Ogre::SceneNode *> _doors;
    Ogre::SceneManager *_sceneManager;
    int score;
    int idx;
    bool _bossEnabled;
    bool _moveCamera;
    int countSpawnersinZone(int zone);

    int getIa() const;

    bool isHuman(ACharacter *character);

    int getClosestHero(ACharacter *achar);

    std::string owner;

    bool checkEnemyCollision(Ogre::Vector3 pos, int idx);

    Dragon *dragon;

    void launch3Projectile(Ogre::SceneManager *pManager, Dragon *pDragon);

    void launchAllProjectile(Ogre::SceneManager *pManager, Dragon *pDragon);

    void setDoors();
};

#endif
