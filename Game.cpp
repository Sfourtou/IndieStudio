#include "Game.h"
#include "InputListener.h"
#include "MoveUtils.h"
#include "Entities/Warrior.h"
#include "LeaderBoard.h"
#include "Entities/Dragon.h"

Game::Game()
        : score(0), owner("") {
    idx = 0;
    zones.push_back(new Zone(1, Ogre::Vector3::ZERO, Ogre::Vector3(-211, -88, 76)));
    zones[0]->setState(ZoneState::COMBAT);
    zones[0]->setEnterIsOpen(true);
    zones.push_back(new Zone(2, Ogre::Vector3(-223, -88, -128), Ogre::Vector3(-157, -88, -173)));
    zones.push_back(new Zone(3, Ogre::Vector3(87, -88, -182), Ogre::Vector3(128, -88, -143)));
    zones.push_back(new Zone(4, Ogre::Vector3(166, -88, 109), Ogre::Vector3(111, -88, 106)));
    zones.push_back(new Zone(5, Ogre::Vector3(-10, -88, 4), Ogre::Vector3(-43, -88, -80)));
    dragon = NULL;
    _bossEnabled = false;
    _moveCamera = true;
}

Game::~Game() {
}

void
Game::moveObjects(const Ogre::FrameEvent &event) {
    for (std::vector<AItem *>::iterator it = drops.begin(); it != drops.end(); ++it) {
        Ogre::AnimationState *anim = (*it)->getAnim();

        anim->setEnabled(true);
        anim->setLoop(true);
        anim->addTime(event.timeSinceLastFrame);
    }
}

void
Game::spawnEnnemies(Ogre::SceneManager *scene, EntitiesFactory *ef, const Ogre::FrameEvent &event) {
    int i;
    int num;
    Ogre::Vector3 npos;
    Ogre::AnimationState *anim;
    int nb = -1;
    bool hero = false;

    for (std::vector<Spawner *>::iterator it = spawners.begin(); it != spawners.end(); ++it) {
        if (!zones[(*it)->getCurrentZone()]->enterIsOpen())
            return;
        if ((*it)->isSpawing()) {
            i = -1;
            num = (*it)->getSpawingNumber();
            const float *v = (*it)->getPos();
            if ((anim = (*it)->spawn()) != 0) {
                anim->setLoop(false);
                anim->setEnabled(true);
            }
            while (++i < 1) {
                npos.x = v[0] - (i * 6);
                npos.y = v[1];
                npos.z = v[2] - 3;
                int random = rand() % 3;
                if (random == 0)
                    addEnnemy(ef->createSorcerer(scene, npos), (*it)->getCurrentZone());
                else if (random == 1)
                    addEnnemy(ef->createGrunt(scene, npos), (*it)->getCurrentZone());
                else
                    addEnnemy(ef->createGhost(scene, npos), (*it)->getCurrentZone());
            }
        }
        anim = (*it)->spawn();
        if (anim->getEnabled()) {
            if (anim->hasEnded()) {
                anim->setEnabled(false);
                anim->setTimePosition(0);
            }
            else
                anim->addTime(event.timeSinceLastFrame);
        }
    }
}

std::vector<ACharacter *> const *
Game::getHeros() const {
    return (&heros);
}

ACharacter *
Game::getHero(int idx) const {
    int i = 0;

    for (std::vector<ACharacter *>::const_iterator it = heros.begin(); it != heros.end(); ++it) {
        if (i == idx)
            return (*it);
        ++i;
    }
    std::cerr << "Cannot get hero at idx " << idx << std::endl;
    return (0);
}

void
Game::addHero(ACharacter *hero, IAType type, Menu *menu) {
    AHero *h;

    if (heros.size() == 0)
        owner = hero->getName();
    heros.push_back(hero);
    hero->setGui(menu->createHeroGui(hero->getName(), hero->getHp(), hero->getMaxHp()));
    if ((h = dynamic_cast<AHero *>(hero)))
        h->setType(type);
}

void
Game::addHero(ACharacter *hero, IAType type, Menu *menu, int hp) {
    AHero *h;

    if (heros.size() == 0)
        owner = hero->getName();
    heros.push_back(hero);
    hero->setGui(menu->createHeroGui(hero->getName(), hero->getHp(), hero->getMaxHp()));
    hero->setHp(hp);
    if ((h = dynamic_cast<AHero *>(hero)))
        h->setType(type);
}

void
Game::addHero(ACharacter *hero, IAType type, Menu *menu, int hp, int zone, int keyNb, int zoneState) {
    AHero *h;

    if (heros.size() == 0)
        owner = hero->getName();
    heros.push_back(hero);
    hero->setGui(menu->createHeroGui(hero->getName(), hero->getHp(), hero->getMaxHp()));
    hero->setHp(hp);
    hero->setCurrentZone(zone);
    hero->setKeyCount(keyNb);
    zones[zone]->setState((ZoneState)zoneState);
    if ((h = dynamic_cast<AHero *>(hero)))
        h->setType(type);
}

void
Game::addHero(std::string const &name, std::string const &heroClass, IAType type, EntitiesFactory *ef,
              Ogre::SceneManager *scene, Keyboard *player1, Keyboard *player2, Menu *menu) {
    Ogre::Vector3 move(0, 0, 0);
    Ogre::Vector3 start = START_POSITION;
    Ogre::Vector3 pos;
    ACharacter *character;

    move.x = heros.size() * 3;
    pos = start + move;
    if (heroClass == "Lutin")
        character = ef->createArcher(scene, pos, type);
    else if (heroClass == "Warrior")
        character = ef->createWarrior(scene, pos, type);
    if (type == HUMAN && heros.size() == 0)
        character->setKey(player1);
    if (type == HUMAN && heros.size() == 1)
        character->setKey(player2);
    character->setName(name);
    addHero(character, type, menu);
}

void
Game::addEnnemy(ACharacter *ennemy, int zone) {
    ennemy->setCurrentZone(zone);
    ennemies.push_back(ennemy);
}

void
Game::addProjectile(Projectile *p) {
    projectiles.push_back(p);
}

void
Game::addDrop(AItem *drop) {
    drops.push_back(drop);
}

void
Game::addSpawner(Spawner *s) {
    spawners.push_back(s);
}


void
Game::deleteHero(ACharacter *hero) {
    for (std::vector<ACharacter *>::iterator it = heros.begin(); it != heros.end(); ++it) {
        if (*it == hero) {
            heros.erase(it);
            return;
        }
    }
}

void Game::attack(Ogre::SceneManager *sceneMgr, const Ogre::FrameEvent &frameEvent) {
    for (int i = 0; i < heros.size(); ++i) {
        if (heros[i]->isAttacking()) {
            Ogre::AnimationState *anim;
            if ((anim = heros[i]->attack()) && !anim->getEnabled() && anim->getTimePosition() == 0) {
                if (heros[i]->getAttackType() == RANGE)
                    launchProjectile(sceneMgr, heros[i]);
                else
                    closeAttack(heros[i], sceneMgr);
                anim->setLoop(false);
                anim->setEnabled(true);
                anim->addTime(frameEvent.timeSinceLastFrame);
            }
            else if (anim && anim->getEnabled() && !anim->hasEnded()) {
                anim->setLoop(false);
                anim->setEnabled(true);
                anim->addTime(frameEvent.timeSinceLastFrame);
            }
            else if (anim && anim->hasEnded()) {
                anim->setEnabled(false);
                anim->setTimePosition(0);
                heros[i]->setIsAttacking(false);
            }
        }
    }
}

int Game::getClosestHero(ACharacter *achar) {
    int idx = 0;
    if (heros.size() <= 0)
        return (-1);
    Ogre::Real dist = achar->getPosition().squaredDistance(heros[0]->getPosition());
    for (int i = 1; i < heros.size(); ++i) {
        Ogre::Real dist2 = achar->getPosition().squaredDistance(heros[i]->getPosition());
        if (dist2 < dist) {
            ++idx;
            dist = dist2;
        }
    }
    return idx;
}

bool Game::checkEnemyCollision(Ogre::Vector3 pos, int idx) {
    for (int i = 0; i < ennemies.size(); ++i) {
        if (i != idx && pos.distance(ennemies[i]->getPosition()) <= 3)
            return (true);
    }
    return (false);
}

void Game::moveEnemies(Ogre::SceneManager *pManager, MOC::CollisionTools *collisionTools,
                       const Ogre::FrameEvent &frameEvent, Ogre::SceneManager *mSceneMgr) {

    for (int i = 0; i < ennemies.size(); ++i) {
        float dist;
        int hero = getClosestHero(ennemies[i]);
        std::cout << hero << std::endl;
        if (hero == -1 || hero > heros.size())
            return;
        ACharacter *character = heros[hero];
        if (ennemies[i]->getPosition().distance(heros[hero]->getPosition()) <= ennemies[i]->getRange()) {
            Ogre::AnimationState *anim;
            if (((anim = ennemies[i]->attack()) != 0 && !anim->getEnabled() && anim->getTimePosition() == 0) ||
                ennemies[i]->getAttackType() == EXPLODE) {
                if (ennemies[i]->getAttackType() == RANGE) {
                    ennemies[i]->setLastDir((heros[hero]->getPosition() - ennemies[i]->getPosition()).normalisedCopy());
                    launchProjectile(mSceneMgr, ennemies[i]);
                }
                else {
                    closeAttack(ennemies[i], mSceneMgr);
                    if (ennemies[i]->getAttackType() == EXPLODE) {
                        Ogre::SceneNode *node = ennemies[i]->getNode();
                        node->removeAndDestroyAllChildren();
                        mSceneMgr->destroySceneNode(node);
                        delete ennemies[i];
                        ennemies.erase(ennemies.begin() + i);
                        --i;
                        continue;
                    }
                }
                anim->setLoop(true);
                anim->setEnabled(true);
                anim->addTime(frameEvent.timeSinceLastFrame);
                Ogre::SceneNode *node1 = ennemies[i]->getNode();
                Ogre::Vector3 apa = node1->getPosition() + ennemies[i]->getLastDir() - node1->getPosition();
                apa.normalise();
                apa.y = 0;
                Ogre::Vector3 test = node1->getOrientation() * Ogre::Vector3::UNIT_Z;
                Ogre::Quaternion q = test.getRotationTo(apa);
                node1->rotate(q);

            }
            else if (anim && anim->getEnabled() && !anim->hasEnded()) {
                anim->setLoop(false);
                anim->setEnabled(true);
                anim->addTime(frameEvent.timeSinceLastFrame);
            }
            else if (anim && anim->hasEnded()) {
                anim->setEnabled(false);
                anim->setTimePosition(0);
                ennemies[i]->setIsAttacking(false);
            }
            continue;
        }
        Ogre::Vector3 dir = (heros[hero]->getPosition()) - (ennemies[i]->getPosition());
        ennemies[i]->setDir(dir);
        dir.normalise();
        dir *= frameEvent.timeSinceLastFrame;
        if (!checkEnemyCollision(ennemies[i]->getPosition() + dir * ennemies[i]->getSpeed(), i)) {
            Ogre::AnimationState *anim;
            if ((anim = ennemies[i]->move(dir)) != 0) {
                anim->setLoop(true);
                anim->setEnabled(true);
                anim->addTime(frameEvent.timeSinceLastFrame);
            }
        }
        else {
            ennemies[i]->setDir(Ogre::Vector3::ZERO);
        }
    }
}


int     Game::countSpawnersinZone(int zone) {
    int nb = 0;
    for (int i = 0; i < spawners.size(); ++i) {
        if (spawners[i]->getCurrentZone() == zone)
            ++nb;
    }
    return (nb);
}

bool Game::isHuman(ACharacter *character) {
    AHero *hero;
    if ((hero = dynamic_cast<AHero *>(character)) != NULL) if (hero->getType() == IAType::HUMAN)
        return (true);
    return (false);
}

int
Game::getEnnemiesInZone(int zone) const {
    int i = -1;
    int nb = 0;

    while (++i < ennemies.size())
        if (ennemies[i]->getCurrentZone() == zone)
            ++nb;
    return (nb);
}

bool isFirst = true;

bool
Game::moveHeros(MOC::CollisionTools *collisionManager, const Ogre::FrameEvent &event, Ogre::SceneNode *camNode,
                int &globalKeyCount, bool checkColl, Ogre::SceneManager *mSceneMgr, Menu *menu) {
    bool hasMove = false;
    float dist = 0;
    Ogre::AnimationState *anim;

    for (auto it = heros.begin(); it != heros.end(); ++it) {
        globalKeyCount += (*it)->getKeyCount();
        Ogre::Vector3 newDir = (*it)->getDir().normalisedCopy();
        newDir *= event.timeSinceLastFrame;
        if ((*it)->getPosition() != (*it)->getPosition() + (newDir * (*it)->getSpeed()))
            hasMove = true;
        if (!checkColl || !collisionManager->collidesWithEntity((*it)->getPosition(),
                                                                (*it)->getPosition() + (newDir * (*it)->getSpeed()),
                                                                dist, 0.0f, 1.0f)) {
            if ((anim = (*it)->move(newDir)) != 0) {
                anim->setLoop(true);
                anim->setEnabled(true);
                anim->addTime(event.timeSinceLastFrame);
                if (it == heros.begin())
                    camNode->translate(newDir * (*it)->getSpeed());
            }
        }
        if ((*it)->getCurrentZone() == zones.size() - 1) {
            if (zones[(*it)->getCurrentZone()]->enterIsOpen()) {
                static int i = -1;
                _bossEnabled = true;
                if (isFirst)
                  dragon->setGui(menu->createDragonGui(dragon->getName(), dragon->getHp(), dragon->getMaxHp()));
                isFirst = false;
                if (++i < 3)
                    _moveCamera = true;
            }
            //bossTime(mSceneMgr);
        }
        else if ((*it)->getCurrentZone() < zones.size() && countSpawnersinZone((*it)->getCurrentZone()) == 0 &&
                 getEnnemiesInZone((*it)->getCurrentZone()) == 0 && !zones[(*it)->getCurrentZone()]->exitIsOpen() &&
                 ((zones[(*it)->getCurrentZone()]->enterIsOpen()) || zones[(*it)->getCurrentZone()]->getId() == 1)) {
                   std::cout << "JE SUIS AU BON ENDROIT" << std::endl;
//          if ((*it)->getCurrentZone() == 0)
//              bossTime(mSceneMgr);
            zones[(*it)->getCurrentZone()]->setExitIsOpen(true);
            Ogre::SceneNode *node = _doors[idx];
            node->removeAndDestroyAllChildren();
            mSceneMgr->destroySceneNode(node);
            ++idx;
            if (isHuman(*it))
                (*it)->setCurrentZone((*it)->getCurrentZone() + 1);
        }
    }
    return (hasMove);
}

void Game::launchProjectile(Ogre::SceneManager *sceneMgr, ACharacter *character) {
    Projectile *projectile;
    if ((projectile = character->attack(sceneMgr)) != NULL && dynamic_cast<Dragon *>(character) != NULL) {
        engine->play2D("../sound/fire_dragon.wav");
        projectiles.push_back(projectile);
    }
    else
      {
        engine->play2D("../sound/shuri.wav");
        projectiles.push_back(projectile);
      }
}

void Game::launch3Projectile(Ogre::SceneManager *pManager, Dragon *pDragon) {
    Projectile *projectile;

    Ogre::Vector3 tmp = Ogre::Vector3(pDragon->getLastDir().x * std::cos(70) + pDragon->getLastDir().z * std::sin(70),
                                      pDragon->getLastDir().y,
                                      -pDragon->getLastDir().x * std::sin(70) + pDragon->getLastDir().z * std::cos(70));
    if ((projectile = pDragon->threeProjectiles(pManager, tmp.normalisedCopy())) != NULL) {
      engine->play2D("../sound/fire_dragon.wav");
      projectiles.push_back(projectile);
    }

    if ((projectile = pDragon->threeProjectiles(pManager, pDragon->getLastDir())) != NULL) {
        projectiles.push_back(projectile);
    }
    tmp = Ogre::Vector3(pDragon->getLastDir().x * std::cos(-70) + pDragon->getLastDir().z * std::sin(-70),
                        pDragon->getLastDir().y,
                        -pDragon->getLastDir().x * std::sin(-70) + pDragon->getLastDir().z * std::cos(-70));

    if ((projectile = pDragon->threeProjectiles(pManager, tmp.normalisedCopy())) != NULL) {
        projectiles.push_back(projectile);
    }
}

void Game::launchAllProjectile(Ogre::SceneManager *pManager, Dragon *pDragon) {
    Projectile *projectile;

    engine->play2D("../sound/fire_dragon.wav");
    for (int i = 0; i < 260; i += 24) {
        Ogre::Vector3 tmp = Ogre::Vector3(
                pDragon->getLastDir().x * std::cos(i) + pDragon->getLastDir().z * std::sin(i),
                pDragon->getLastDir().y,
                -pDragon->getLastDir().x * std::sin(i) + pDragon->getLastDir().z * std::cos(i));
        if ((projectile = pDragon->threeProjectiles(pManager, tmp.normalisedCopy())) != NULL) {
            projectiles.push_back(projectile);
        }
    }
}

void
Game::moveProjectile(MOC::CollisionTools *collisionManager, Ogre::Real timeSinceLastFrame,
                     Ogre::SceneManager *mSceneMgr) {
    for (int i = 0; i < projectiles.size();) {
        Ogre::AnimationState *anim;
        anim = projectiles[i]->move(timeSinceLastFrame);
        anim->setLoop(true);
        anim->setEnabled(true);
        anim->addTime(timeSinceLastFrame);
        if (projectiles[i]->getDistance() >= projectiles[i]->getRange()) {
            projectiles[i]->getNode()->removeAndDestroyAllChildren();
            mSceneMgr->destroySceneNode(projectiles[i]->getNode());
            delete projectiles[i];
            projectiles.erase(projectiles.begin() + i);
        }
        else if (checkCollision(collisionManager, projectiles[i], mSceneMgr)) // AJOUTE DU SCORE AU JOUEUR
        {
            score += ADD_KILL;
            projectiles[i]->getNode()->removeAndDestroyAllChildren();
            mSceneMgr->destroySceneNode(projectiles[i]->getNode());
            delete projectiles[i];
            projectiles.erase(projectiles.begin() + i);
        }
        else
            ++i;
    }
}

bool Game::checkCollision(MOC::CollisionTools *collisionManager, Projectile *&projectile,
                          Ogre::SceneManager *&mSceneMgr) {
    AItem *item;
    ACharacter *launcher;
    Ogre::Vector3 vector;
    float x1, z1;

    vector = projectile->getPos();
    x1 = vector.x;
    z1 = vector.z;
    if (projectile->isHero()) {
        for (int i = 0; i < ennemies.size(); ++i) {
            float x2, z2;
            float dist;
            vector = ennemies[i]->getPosition();
            x2 = vector.x;
            z2 = vector.z;
            dist = abs((int) sqrt(pow(x2 - x1, 2) + pow(z2 - z1, 2)));
            if (dist <= 1) {
                ennemies[i]->setHp(ennemies[i]->getHp() - projectile->getDamage());
                if (ennemies[i]->getHp() <= 0) {
                    if ((item = ennemies[i]->onDie(mSceneMgr)))
                        addDrop(item);
                    ennemies[i]->die();
                    ennemies[i]->getNode()->removeAndDestroyAllChildren();
                    mSceneMgr->destroySceneNode(ennemies[i]->getNode());
                    delete ennemies[i];
                    ennemies.erase(ennemies.begin() + i);
                }
                return true;
            }
        }
        for (int y = 0; y < spawners.size(); ++y) {
            if ((projectile->getPos().distance(spawners[y]->getNode()->getPosition()) <= 2)) {
                spawners[y]->setHp(spawners[y]->getHp() - projectile->getDamage());
                if (spawners[y]->getHp() <= 0) {
                    if ((item = spawners[y]->onDie(mSceneMgr)))
                        addDrop(item);
                    spawners[y]->getNode()->removeAndDestroyAllChildren();
                    mSceneMgr->destroySceneNode(spawners[y]->getNode());
                    delete spawners[y];
                    spawners.erase(spawners.begin() + y);
                    return true;
                }
                return true;
            }
        }
        if (dragon) {
            if ((projectile->getPos().distance(dragon->getNode()->getPosition()) <= 2)) {
                dragon->setHp(dragon->getHp() - projectile->getDamage());
                std::cout << "HP Dragon : " << dragon->getHp() << std::endl;
                if (dragon->getHp() <= 0) {
                    if ((item = dragon->onDie(mSceneMgr)))
                        addDrop(item);
                    dragon->setDead();
                }
                return true;
            }
        }
    }
    else {
        for (int i = 0; i < heros.size(); ++i) {
            float x2, z2;
            float dist;
            vector = heros[i]->getPosition();
            x2 = vector.x;
            z2 = vector.z;
            dist = abs((int) sqrt(pow(x2 - x1, 2) + pow(z2 - z1, 2)));
            if (dist <= 1) {
                heros[i]->setHp(heros[i]->getHp() - projectile->getDamage());
                if (heros[i]->getHp() <= 0) {
                    if ((item = heros[i]->onDie(mSceneMgr)))
                        addDrop(item);
                    heros[i]->die();
                    heros[i]->getNode()->removeAndDestroyAllChildren();
                    mSceneMgr->destroySceneNode(heros[i]->getNode());
                    delete heros[i];
                    heros.erase(heros.begin() + i);
                    std::cout << heros.size() << std::endl;
                }
                return true;
            }
        }
    }

    return false;
}

void
Game::checkDrop(Ogre::SceneManager *scene, Menu *menu) {
    for (auto hero = heros.begin(); hero != heros.end(); ++hero) {
        Ogre::Vector3 vector;
        APowerUp *tmp;
        float x1, z1;

        vector = (*hero)->getPosition();
        x1 = vector.x;
        z1 = vector.z;
        for (std::vector<AItem *>::iterator drop = drops.begin(); drop != drops.end(); ++drop) {
            float x2, z2;
            float dist;
            vector = (*drop)->getNode()->getPosition();
            x2 = vector.x;
            z2 = vector.z;
            dist = abs((int) sqrt(pow(x2 - x1, 2) + pow(z2 - z1, 2)));
            if (dist <= 1) {
                (*drop)->onTake(dynamic_cast<ACharacter *>(*hero), engine);
                (*drop)->getNode()->removeAndDestroyAllChildren();
                scene->destroySceneNode((*drop)->getNode());
                if ((tmp = dynamic_cast<APowerUp *>(*drop)))
                    powerUps.push_back(tmp);
                else
                    delete *drop;
                drops.erase(drop);
                return;
            }
        }
    }
}

int    Game::getIa() const {
    for (int i = 0; i < heros.size(); ++i) {
        AHero *charac;
        if ((charac = dynamic_cast<AHero *>(heros[i])) != NULL) {
            {
                if (charac->getType() == IAType::COMPUTER)
                    return (i);
            }
        }
    }
    return (-1);
}

void Game::moveAi(MOC::CollisionTools *collisionTools, const Ogre::FrameEvent &event, Ogre::SceneManager *pManager,
                  int &globalKeyCount) {
    Ogre::Vector3 dir(Ogre::Vector3::ZERO);
    int idx = getIa();
    if (idx == -1)
        return;
    ACharacter *character = getHero(idx);
    if (character->getCurrentZone() >= zones.size())
        return;
    std::cout << "MOUVE AI" << std::endl;
    if (zones[character->getCurrentZone()]->getState() == ZoneState::START) {
        std::cout << "START" << std::endl;
        if (character->getPosition().distance(zones[character->getCurrentZone()]->getStartZonePosition()) <= 1.0f)
            zones[character->getCurrentZone()]->setState(ZoneState::COMBAT);
        else if (MoveUtils::canGoStraightAhead(collisionTools, character->getPosition(),
                                               zones[character->getCurrentZone()]->getStartZonePosition(), 1.0f))
            dir = MoveUtils::getDirection(character->getPosition(),
                                          zones[character->getCurrentZone()]->getStartZonePosition());
    }
    if (zones[character->getCurrentZone()]->getState() == ZoneState::COMBAT) {
        std::cout << "COMBAT" << std::endl;
        Projectile *proj;
        for (int i = 0; i < ennemies.size(); ++i) {
            if (ennemies[i]->getCurrentZone() == character->getCurrentZone() && !character->isAttacking()) {
                if (character->getPosition().distance(ennemies[i]->getPosition()) >= character->getRange()) {
                    dir = ennemies[i]->getPosition() - character->getPosition();
                    break;
                }
                character->setLastDir((ennemies[i]->getPosition() - character->getPosition()).normalisedCopy());
                character->setIsAttacking(true);
                break;
            }
        }
        for (int i = 0; i < spawners.size(); ++i) {
            if (spawners[i]->getCurrentZone() == character->getCurrentZone() && !character->isAttacking()) {
                if (character->getPosition().distance(spawners[i]->getPosition()) >= character->getRange()) {
                    dir = spawners[i]->getPosition() - character->getPosition();
                    break;
                }
                character->setLastDir((spawners[i]->getPosition() - character->getPosition()).normalisedCopy());
                character->setIsAttacking(true);
                break;
            }
        }
        if (character->getCurrentZone() == zones.size() - 1 && dragon != NULL) {
            if (character->getPosition().distance(dragon->getPosition()) >= character->getRange()) {
                dir = dragon->getPosition() - character->getPosition();
            }
            else {
                character->setLastDir((dragon->getPosition() - character->getPosition()).normalisedCopy());
                character->setIsAttacking(true);
            }
        }
        else if (getEnnemiesInZone(character->getCurrentZone()) == 0 &&
                 countSpawnersinZone(character->getCurrentZone()) == 0 ||
                 (character->getCurrentZone() == zones.size() - 1 && dragon == NULL)) {
            if (globalKeyCount == 0 && drops.size())
                dir = drops[0]->getNode()->getPosition() - character->getPosition();
            else
                zones[character->getCurrentZone()]->setState(ZoneState::TARGET);
        }
    }
    if (zones[character->getCurrentZone()]->getState() == ZoneState::TARGET) {
        std::cout << "TARGET" << std::endl;
        if (character->getPosition().distance(zones[character->getCurrentZone()]->getTargetPosition()) <= 1.0f) {
            std::cout << character->getPosition() << std::endl;
            std::cout << "j'ouvre la porte " << zones[character->getCurrentZone()]->getTargetPosition() << std::endl;
            zones[character->getCurrentZone()]->setState(ZoneState::NEXTZONE);
        }
        else if (MoveUtils::canGoStraightAhead(collisionTools, character->getPosition(),
                                               zones[character->getCurrentZone()]->getTargetPosition(), 1.0f))
            dir = zones[character->getCurrentZone()]->getTargetPosition() - character->getPosition();
    }
    if (zones[character->getCurrentZone()]->getState() == ZoneState::NEXTZONE) {
        std::cout << "NEXTZONE" << std::endl;
        if (character->getPosition().distance(zones[character->getCurrentZone()]->getPosition()) <= 1.0f)
            zones[character->getCurrentZone()]->getNextPosition();
        std::cout << zones[character->getCurrentZone()]->getPosition() << std::endl;
        if (zones[character->getCurrentZone()]->getPosition().x == 0 &&
            zones[character->getCurrentZone()]->getPosition().y == 0 &&
            zones[character->getCurrentZone()]->getPosition().z == 0) {
            std::cout << "ZONE:" << character->getCurrentZone();

            zones[character->getCurrentZone()]->setState(ZoneState::START);
            character->setCurrentZone(character->getCurrentZone() + 1);
            if (character->getCurrentZone() < zones.size()) {
                zones[character->getCurrentZone()]->setState(ZoneState::START);
                if (character->getCurrentZone() < zones.size())
                    openTheDoor(pManager, character, 0);
            }
        }
        else if (MoveUtils::canGoStraightAhead(collisionTools, character->getPosition(),
                                               zones[character->getCurrentZone()]->getPosition(), 1.0f)) {
            int idx = getHuman();
            if (idx == -1 || character->getPosition().squaredDistance(getHero(idx)->getPosition()) <= 300)
                dir = MoveUtils::getDirection(character->getPosition(),
                                              zones[character->getCurrentZone()]->getPosition());
        }
    }
    character->setDir(dir);
}


int
Game::getScore() const {
    return (score);
}

std::vector<ACharacter *>
Game::getEnnemies() const {
    return (ennemies);
}

std::vector<AItem *>
Game::getDrops() const {
    return (drops);
}

std::vector<Spawner *>
Game::getSpawners() const {
    return (spawners);
}

std::vector<Projectile *>
Game::getProjectiles() const {
    return (projectiles);
}

std::vector<Zone *>
Game::getZones() const {
    return (zones);
}

void
Game::setScore(int nscore) {
    score = nscore;
}

void    Game::dropsLoop() {
    APowerUp *tmp;

    for (std::vector<APowerUp *>::iterator it = powerUps.begin(); it != powerUps.end(); ++it) {
        if ((tmp = dynamic_cast<APowerUp *>(*it))) {
            if (tmp->checkIfActive() == false) {
                tmp->finishEffect();
                it = powerUps.erase(it);
                return;
            }
        }
    }
}

int   Game::getHuman() const {
    for (int i = 0; i < heros.size(); ++i) {
        AHero *charac;
        if ((charac = dynamic_cast<AHero *>(heros[i])) != NULL) {
            if (charac->getType() == IAType::HUMAN)
                return (i);
        }
    }
    return (-1);
}

void
Game::initGame(Menu *menu, EntitiesFactory *ef, Ogre::SceneManager *scene, Keyboard *player1, Keyboard *player2) {
    Spawner *spawnerZone11;
    Spawner *spawnerZone21;
    Spawner *spawnerZone22;
    Spawner *spawnerZone31;
    Spawner *spawnerZone32;
    Spawner *spawnerZone33;
    Spawner *spawnerZone41;
    Spawner *spawnerZone42;
    Spawner *spawnerZone43;
    Spawner *spawnerZone44;

    Ogre::Vector3 v1 = Ogre::Vector3(-211, -88, 98);
    spawnerZone11 = ef->createSpawner(scene, v1);
    spawnerZone11->setCurrentZone(0);
    addSpawner(spawnerZone11);

    v1 = Ogre::Vector3(-210, -88, -170);
    spawnerZone21 = ef->createSpawner(scene, v1);
    spawnerZone21->setCurrentZone(1);
    addSpawner(spawnerZone21);

    v1 = Ogre::Vector3(-175, -88, -125);
    spawnerZone22 = ef->createSpawner(scene, v1);
    spawnerZone22->setCurrentZone(1);
    addSpawner(spawnerZone22);

    v1 = Ogre::Vector3(125, -88, -210);
    spawnerZone31 = ef->createSpawner(scene, v1);
    spawnerZone31->setCurrentZone(2);
    addSpawner(spawnerZone31);

    v1 = Ogre::Vector3(160, -88, -185);
    spawnerZone32 = ef->createSpawner(scene, v1);
    spawnerZone32->setCurrentZone(2);
    addSpawner(spawnerZone32);

    v1 = Ogre::Vector3(130, -88, -150);
    spawnerZone33 = ef->createSpawner(scene, v1);
    spawnerZone33->setCurrentZone(2);
    addSpawner(spawnerZone33);

    v1 = Ogre::Vector3(170, -88, 135);
    spawnerZone41 = ef->createSpawner(scene, v1);
    spawnerZone41->setCurrentZone(3);
    addSpawner(spawnerZone41);

    v1 = Ogre::Vector3(145, -88, 165);
    spawnerZone42 = ef->createSpawner(scene, v1);
    spawnerZone42->setCurrentZone(3);
    addSpawner(spawnerZone42);

    v1 = Ogre::Vector3(105, -88, 140);
    spawnerZone43 = ef->createSpawner(scene, v1);
    spawnerZone43->setCurrentZone(3);
    addSpawner(spawnerZone43);

    v1 = Ogre::Vector3(140, -88, 135);
    spawnerZone44 = ef->createSpawner(scene, v1);
    spawnerZone44->setCurrentZone(3);
    addSpawner(spawnerZone44);
}

void Game::addDoor(Ogre::SceneNode *node) {
    _doors.push_back(node);
}

bool Game::closeAttack(ACharacter *character, Ogre::SceneManager *mSceneMgr) {
    AItem *item;
    ACharacter *launcher;
    Ogre::Vector3 vector;
    float x1, z1;

    vector = character->getPosition();
    x1 = vector.x;
    z1 = vector.z;
    if (character->isHero()) {
        for (int i = 0; i < ennemies.size(); ++i) {
            float x2, z2;
            float dist;
            vector = ennemies[i]->getPosition();
            x2 = vector.x;
            z2 = vector.z;
            dist = abs((int) sqrt(pow(x2 - x1, 2) + pow(z2 - z1, 2)));
            if (dist <= character->getRange()) {
                ennemies[i]->setHp(ennemies[i]->getHp() - character->getDamage());
                if (ennemies[i]->getHp() <= 0) {
                    if ((item = ennemies[i]->onDie(mSceneMgr)))
                        addDrop(item);
                    ennemies[i]->die();
                    ennemies[i]->getNode()->removeAndDestroyAllChildren();
                    mSceneMgr->destroySceneNode(ennemies[i]->getNode());
                    delete ennemies[i];
                    ennemies.erase(ennemies.begin() + i);
                    score += ADD_KILL;
                }
            }
        }
        for (int y = 0; y < spawners.size(); ++y) {
            if ((character->getPosition().distance(spawners[y]->getNode()->getPosition()) <= character->getRange())) {
                spawners[y]->setHp(spawners[y]->getHp() - character->getDamage());
                if (spawners[y]->getHp() <= 0) {
                    if ((item = spawners[y]->onDie(mSceneMgr)))
                        addDrop(item);
                    spawners[y]->getNode()->removeAndDestroyAllChildren();
                    mSceneMgr->destroySceneNode(spawners[y]->getNode());
                    delete spawners[y];
                    spawners.erase(spawners.begin() + y);
                    score += ADD_KILL;
                }
            }
        }
        if (dragon) {
            if ((character->getPosition().distance(dragon->getNode()->getPosition()) <= character->getRange())) {
                dragon->setHp(dragon->getHp() - character->getDamage());
                if (dragon->getHp() <= 0) {
                    if ((item = dragon->onDie(mSceneMgr)))
                        addDrop(item);
                    dragon->setDead();
                }
            }
        }
    }
    else {
        for (int i = 0; i < heros.size(); ++i) {
            float x2, z2;
            float dist;
            vector = heros[i]->getPosition();
            x2 = vector.x;
            z2 = vector.z;
            dist = abs((int) sqrt(pow(x2 - x1, 2) + pow(z2 - z1, 2)));
            if (dist <= character->getRange()) {
                heros[i]->setHp(heros[i]->getHp() - character->getDamage());
                if (heros[i]->getHp() <= 0) {
                    if ((item = heros[i]->onDie(mSceneMgr)))
                        addDrop(item);
                    heros[i]->die();
                    heros[i]->getNode()->removeAndDestroyAllChildren();
                    mSceneMgr->destroySceneNode(heros[i]->getNode());
                    delete heros[i];
                    heros.erase(heros.begin() + i);
                    std::cout << heros.size() << std::endl;
                }
                return true;
            }
        }
    }
    return false;
}

void Game::openTheDoor(Ogre::SceneManager *pManager, ACharacter *pCharacter, int key) {
    Ogre::Real real;
    if (pCharacter->getCurrentZone() < zones.size() &&
        (pCharacter->getPosition().distance(zones[pCharacter->getCurrentZone()]->getStartZonePosition())) <=
        10.0f) { //&& pCharacter->getKeyCount() > 0) {
        zones[pCharacter->getCurrentZone()]->setEnterIsOpen(true);
        Ogre::SceneNode *node = _doors[idx];
        node->removeAndDestroyAllChildren();
        pManager->destroySceneNode(node);
        ++idx;
        pCharacter->setKeyCount(pCharacter->getKeyCount() - 1);
    }
}

bool
Game::checkEnd() const {
  if (heros.size() == 0)
    return true;
  for (auto it = heros.begin(); it != heros.end(); ++it)
  {
    Ogre::Vector3 const &pos = (*it)->getPosition();
    if (pos.x <= -54 && pos.x >= -55 && pos.z <= -130 && pos.z >= -136)
      return true;
  }
  return false;
}

void
Game::clearResources(Ogre::SceneManager *scene) {
    Ogre::SceneNode *node;

    for (auto it = powerUps.begin(); it != powerUps.end();) {
        delete *it;
        it = powerUps.erase(it);
    }

    for (auto it = ennemies.begin(); it != ennemies.end();) {
        node = (*it)->getNode();
        node->removeAndDestroyAllChildren();
        scene->destroySceneNode(node);
        delete *it;
        it = ennemies.erase(it);
    }
    for (auto it = heros.begin(); it != heros.end();) {
        node = (*it)->getNode();
        node->removeAndDestroyAllChildren();
        scene->destroySceneNode(node);
        delete *it;
        it = heros.erase(it);
    }
    for (auto it = drops.begin(); it != drops.end();) {
        node = (*it)->getNode();
        node->removeAndDestroyAllChildren();
        scene->destroySceneNode(node);
        delete *it;
        it = drops.erase(it);
    }
    for (auto it = spawners.begin(); it != spawners.end();) {
        node = (*it)->getNode();
        node->removeAndDestroyAllChildren();
        scene->destroySceneNode(node);
        delete *it;
        it = spawners.erase(it);
    }
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        node = (*it)->getNode();
        node->removeAndDestroyAllChildren();
        scene->destroySceneNode(node);
        delete *it;
        it = projectiles.erase(it);
    }
    for (;idx < _doors.size(); ++idx)
    {
        node = _doors[idx];
        node->removeAndDestroyAllChildren();
        scene->destroySceneNode(node);
    }
    _doors.clear();
    idx = 0;
    for (int i = 0; i < zones.size(); ++i)
    {
        zones[i]->setState(START);
        zones[i]->setExitIsOpen(false);
        zones[i]->setEnterIsOpen(false);
        if (i == 0) {
            zones[i]->setState(COMBAT);
            zones[i]->setEnterIsOpen(true);
        }
    }
    score = 0;
    setDoors();
}

std::string const &
Game::getOwner() const {
    return (owner);
}


void
Game::setOwner(std::string const &o) {
    owner = o;
}

void Game::bossPattern(Ogre::SceneManager *mSceneMgr, Ogre::FrameEvent frameEvent) {

    if (dragon && dragon->getHp() > 0) {
        int hero = getClosestHero(dragon);
        if (hero == -1 || hero > heros.size())
            return;
        ACharacter *character = heros[hero];
        Ogre::AnimationState *anim;
        if ((anim = dragon->attack()) != 0 && !anim->getEnabled() && anim->getTimePosition() == 0) {
            dragon->setLastDir((heros[hero]->getPosition() - dragon->getPosition()).normalisedCopy());
            if (dragon->getHp() > 999)
                launchProjectile(mSceneMgr, dragon);
            else if (dragon->getHp() > 499)
                launch3Projectile(mSceneMgr, dragon);
            else
                launchAllProjectile(mSceneMgr, dragon);
            anim->setLoop(true);
            anim->setEnabled(true);
            anim->addTime(frameEvent.timeSinceLastFrame);
            Ogre::SceneNode *node1 = dragon->getNode();
            Ogre::Vector3 apa = node1->getPosition() + dragon->getLastDir() - node1->getPosition();
            apa.normalise();
            apa.y = 0;
            Ogre::Vector3 test = node1->getOrientation() * Ogre::Vector3::UNIT_Z;
            Ogre::Quaternion q = test.getRotationTo(apa);
            node1->rotate(q);
        }
        else if (anim && anim->getEnabled() && !anim->hasEnded()) {
            anim->setLoop(false);
            anim->setEnabled(true);
            anim->addTime(frameEvent.timeSinceLastFrame);
        }
        else if (anim && anim->hasEnded()) {
            anim->setEnabled(false);
            anim->setTimePosition(0);
            dragon->setIsAttacking(false);
        }
    }
    else if (dragon && dragon->isDead()) {
        Ogre::AnimationState *die;
        dragon->attack()->setEnabled(false);
        if ((die = dragon->die()) != 0 && !die->getEnabled() && die->getTimePosition() == 0) {
            die->setLoop(false);
            die->setEnabled(true);
        }
        else if (die && die->getEnabled() && !die->hasEnded()) {
            die->setLoop(false);
            die->setEnabled(true);
            die->addTime(frameEvent.timeSinceLastFrame);
        }
        else if (die && die->hasEnded()) {
            die->setEnabled(false);
            die->setTimePosition(0);
            dragon->getNode()->removeAndDestroyAllChildren();
            mSceneMgr->destroySceneNode(dragon->getNode());
            delete dragon;
            dragon = NULL;
            score += KILL_DRAGON;
            if (zones.size() > 0)
                zones[zones.size() - 1]->setExitIsOpen(true);
            Ogre::SceneNode *node = _doors[idx];
            node->removeAndDestroyAllChildren();
            mSceneMgr->destroySceneNode(node);
            ++idx;
        }
    }
}

void Game::bossTime(Ogre::SceneManager *pManager) {
    Ogre::Entity *mDragon = pManager->createEntity("Dragon.mesh");
    Ogre::SceneNode *dragonNode = pManager->getRootSceneNode()->createChildSceneNode("dragon", BOSS_POSITION);
    dragonNode->scale(0.6, 0.6, 0.6);
    dragonNode->attachObject(mDragon);
    dragon = new Dragon(dragonNode, mDragon->getAnimationState("intro"), mDragon->getAnimationState("attack1"),
                        mDragon->getAnimationState("attack2"), mDragon->getAnimationState("attack3"),
                        mDragon->getAnimationState("die"));
}

void Game::loadEverything(Ogre::SceneManager *pManager) const {
    Ogre::Entity *demon = pManager->createEntity("MyDemon.mesh");
    Ogre::Entity *ogre = pManager->createEntity("Ogre.mesh");
    Ogre::Entity *ghost = pManager->createEntity("Ghost.mesh");
    Ogre::Entity *lutin = pManager->createEntity("Lutin.mesh");
    Ogre::Entity *warrior = pManager->createEntity("Warrior.mesh");
    Ogre::Entity *claquette = pManager->createEntity("Claquette.mesh");
    Ogre::Entity *key = pManager->createEntity("Key.mesh");
    Ogre::Entity *potion = pManager->createEntity("LifePotion.mesh");
    Ogre::Entity *sword = pManager->createEntity("Sword.mesh");
    Ogre::Entity *shuri = pManager->createEntity("Shuriken.mesh");
    Ogre::Entity *fireball = pManager->createEntity("Sphere.mesh");
    Ogre::Entity *dragon = pManager->createEntity("Dragon.mesh");

    pManager->destroyEntity(demon);
    pManager->destroyEntity(ogre);
    pManager->destroyEntity(ghost);
    pManager->destroyEntity(lutin);
    pManager->destroyEntity(warrior);
    pManager->destroyEntity(claquette);
    pManager->destroyEntity(key);
    pManager->destroyEntity(potion);
    pManager->destroyEntity(sword);
    pManager->destroyEntity(shuri);
    pManager->destroyEntity(fireball);
    pManager->destroyEntity(dragon);
}

bool Game::bossIsEnabled() const {
    return _bossEnabled;
}

bool Game::moveCamera() const {
    return _moveCamera;
}

void Game::setMoveCamera(bool moveCamera) {
    _moveCamera = moveCamera;
}

void
Game::setDoors(int doorsNumber)
{
  while (_doors.size() > 0 && _doors.size() != doorsNumber)
    {
      _doors.erase(_doors.begin());
    }
}

int
Game::getDoorsLength() const
{
  return (_doors.size());
}


int
Game::getIdx() const
{
  return (idx);
}

void
Game::setIdx(int nidx, Ogre::SceneManager *scene)
{
  Ogre::SceneNode *node;
  int tab[9] = {0, 1, 1, 2, 2, 3, 3, 4, 4};

  idx = nidx;
  for (int i = 0; i < zones.size(); ++i)
  {
    zones[i]->setEnterIsOpen(false);
    zones[i]->setExitIsOpen(false);
  }
  for (int i = 0; i <= idx; ++i)
  {
    zones[tab[i]]->setEnterIsOpen(true);
    if (i != idx)
    {
      node = _doors[i];
      node->removeAndDestroyAllChildren();
      scene->destroySceneNode(node);
      // zones[tab[i]]->setExitIsOpen(true);
    }
  }
}

void Game::setSceneManager(Ogre::SceneManager *sceneManager) {
    _sceneManager = sceneManager;
}

void    Game::setDoors()
{
    Ogre::Entity* door = _sceneManager->createEntity("Doors.mesh");
    Ogre::Entity* door1 = _sceneManager->createEntity("Doors.001.mesh");
    Ogre::Entity* door2 = _sceneManager->createEntity("Doors.002.mesh");
    Ogre::Entity* door3 = _sceneManager->createEntity("Doors.003.mesh");
    Ogre::Entity* door4 = _sceneManager->createEntity("Doors.004.mesh");
    Ogre::Entity* door5 = _sceneManager->createEntity("Doors.005.mesh");
    Ogre::Entity* door6 = _sceneManager->createEntity("Doors.006.mesh");
    Ogre::Entity* door7 = _sceneManager->createEntity("Doors.007.mesh");
    Ogre::Entity* door8 = _sceneManager->createEntity("Doors.008.mesh");
    Ogre::SceneNode* DoorsNode = _sceneManager->getRootSceneNode()->createChildSceneNode("doors");
    Ogre::SceneNode* DoorsNode1 = _sceneManager->getRootSceneNode()->createChildSceneNode("doors1");
    Ogre::SceneNode* DoorsNode2 = _sceneManager->getRootSceneNode()->createChildSceneNode("doors2");
    Ogre::SceneNode* DoorsNode3 = _sceneManager->getRootSceneNode()->createChildSceneNode("doors3");
    Ogre::SceneNode* DoorsNode4 = _sceneManager->getRootSceneNode()->createChildSceneNode("doors4");
    Ogre::SceneNode* DoorsNode5 = _sceneManager->getRootSceneNode()->createChildSceneNode("doors5");
    Ogre::SceneNode* DoorsNode6 = _sceneManager->getRootSceneNode()->createChildSceneNode("doors6");
    Ogre::SceneNode* DoorsNode7 = _sceneManager->getRootSceneNode()->createChildSceneNode("doors7");
    Ogre::SceneNode* DoorsNode8 = _sceneManager->getRootSceneNode()->createChildSceneNode("doors8");
    DoorsNode->attachObject(door);
    DoorsNode1->attachObject(door1);
    DoorsNode2->attachObject(door2);
    DoorsNode3->attachObject(door3);
    DoorsNode4->attachObject(door4);
    DoorsNode5->attachObject(door5);
    DoorsNode6->attachObject(door6);
    DoorsNode7->attachObject(door7);
    DoorsNode8->attachObject(door8);
    DoorsNode->scale(60.8,60.8,60.8);
    DoorsNode1->scale(60.8,60.8,60.8);
    DoorsNode2->scale(60.8,60.8,60.8);
    DoorsNode3->scale(60.8,60.8,60.8);
    DoorsNode4->scale(60.8,60.8,60.8);
    DoorsNode5->scale(60.8,60.8,60.8);
    DoorsNode6->scale(60.8,60.8,60.8);
    DoorsNode7->scale(60.8,60.8,60.8);
    DoorsNode8->scale(60.8,60.8,60.8);
    DoorsNode->setPosition(0, -100, 0);
    DoorsNode1->setPosition(0, -100, 0);
    DoorsNode2->setPosition(0, -100, 0);
    DoorsNode3->setPosition(0, -100, 0);
    DoorsNode4->setPosition(0, -100, 0);
    DoorsNode5->setPosition(0, -100, 0);
    DoorsNode6->setPosition(0, -100, 0);
    DoorsNode7->setPosition(0, -100, 0);
    DoorsNode8->setPosition(0, -100, 0);
    addDoor(DoorsNode);
    addDoor(DoorsNode6);
    addDoor(DoorsNode5);
    addDoor(DoorsNode4);
    addDoor(DoorsNode3);
    addDoor(DoorsNode2);
    addDoor(DoorsNode1);
    addDoor(DoorsNode7);
    addDoor(DoorsNode8);
}

bool
Game::dragonIsAlive() const
{
  return (!!dragon);
}
