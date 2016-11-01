#include "Entities/EntitiesFactory.h"
#include "InputListener.h"
#include "Game.h"
#include "Menu.hh"

Menu::Menu(Ogre::SceneManager *mSceneMgr, OIS::Mouse *mMouse, OIS::Keyboard *mKeyboard, Ogre::RenderWindow *mWindow, InputListener *il)
  : mOverlaySystem(0), mTrayMgr(0), keyButton(0), scoreButton(0), heroGuis(0), gameButton(0), loadButton(0), settingButton(0), humanNumberButton(0), iaNumberButton(0), ia(0), human(0), fullScreenConfig(0), returnButton(0), playerClass(0), playerName(0), state(SPLASHSCREEN), lastButton(""), selectCharIdx(0)
{
  OgreBites::InputContext ic;

  _player1 = 0;
  _player2 = 0;
  over = false;
  ic.mMouse = mMouse;
  ic.mKeyboard = mKeyboard;
  mOverlaySystem = new Ogre::OverlaySystem();
  mSceneMgr->addRenderQueueListener(mOverlaySystem);
  Ogre::ResourceGroupManager  &mRgMgr  = Ogre::ResourceGroupManager::getSingleton();
  mRgMgr.createResourceGroup(RESOURCE_GROUP_FRAMEWORK);
  mRgMgr.addResourceLocation("../media/packs/SdkTrays.zip", "Zip", RESOURCE_GROUP_FRAMEWORK);
  mRgMgr.initialiseAllResourceGroups();
  mTrayMgr = new OgreBites::SdkTrayManager("TrayManager", mWindow, ic, il);
  keyButton = 0;
  resetInitState();
  engine = irrklang::createIrrKlangDevice();
}

Menu::~Menu()
{
  delete mOverlaySystem;
  delete mTrayMgr;
  if (keyButton)
    delete keyButton;
  if (heroGuis)
  {
    for (auto it = heroGuis->begin(); it != heroGuis->end(); ++it)
      delete *it;
    delete heroGuis;
  }
}

void
Menu::createKeyGUI()
{
  keyButton = mTrayMgr->createButton(OgreBites::TL_TOPRIGHT, "KeyNumberGUI", "Clés : 0", WIDTH_UI / 2);
}

void
Menu::updateKeyGUI(int keyNum)
{
  keyButton->setCaption("keys: " + std::to_string(keyNum));
}

void
Menu::createScoreGUI()
{
  scoreButton = mTrayMgr->createButton(OgreBites::TL_TOPRIGHT, "ScoreGUI", "Score : 0", WIDTH_UI / 2);
}

void
Menu::updateScoreGUI(int score)
{
  scoreButton->setCaption("Score: " + std::to_string(score));
}

guiHero *
Menu::createHeroGui(std::string const &playername, int life, int maxLife)
{
  guiHero *hero = new guiHero();
  static int hash = 0;

  hero->playername = mTrayMgr->createButton(OgreBites::TL_TOPRIGHT, "Button" + std::to_string(hash), playername, WIDTH_UI / 2);
  hero->bar =  mTrayMgr->SdkTrayManager::createProgressBar(OgreBites::TL_TOPRIGHT, "ProgressBar" + std::to_string(hash++), "Vie", WIDTH_UI / 2, WIDTH_UI / 2);
  hero->bar->setProgress((float)life / (float)maxLife);
  mTrayMgr->SdkTrayManager::createSeparator(OgreBites::TL_TOPRIGHT, "Separator" + std::to_string(hash), WIDTH_UI / 2);
  return (hero);
}

guiHero *
Menu::createDragonGui(std::string const &playername, int life, int maxLife)
{
  guiHero *hero = new guiHero();
  static int hash = 0;

  hero->playername = mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "DragonGui", playername, WIDTH_UI / 2);
  hero->bar =  mTrayMgr->SdkTrayManager::createProgressBar(OgreBites::TL_TOPLEFT, "ProgressBarGui", "Vie", WIDTH_UI / 2, WIDTH_UI / 2);
  hero->bar->setProgress((float)life / (float)maxLife);
  return (hero);
}

void
Menu::createLaunchMenu()
{
  selectCharIdx = 0;
  deleteAllButton();
  mTrayMgr->showCursor();
  mTrayMgr->setListener(this);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "TitleButton", "Gauntlet", WIDTH_UI);
  mTrayMgr->SdkTrayManager::createSeparator(OgreBites::TL_CENTER, "GeneralMenuSeparator", WIDTH_UI);
  gameButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "New Game", "New Game", WIDTH_UI);
  loadButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "Load Game", "Load Game", WIDTH_UI);
  loadButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "ScoreButton", "Score", WIDTH_UI);
  settingButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "Settings", "Settings", WIDTH_UI);
  mTrayMgr->SdkTrayManager::createSeparator(OgreBites::TL_CENTER, "GeneralMenuSeparator2", WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "QuitButton", "Quitter le jeu", WIDTH_UI);
  initState[GENERAL_MENU] = true;
}


OgreBites::SdkTrayManager *
Menu::getTrayMgr() const
{
  return (mTrayMgr);
}

void
Menu::buttonHit(OgreBites::Button *button)
{
  int value;

  engine->play2D("../sound/click.wav");
  lastButtonPressed = button;
  if (button->getName() == "New Game")
    state = NEW_GAME;
  else if (button->getName() == "Load Game")
    {
      deleteAllButton();
      resetInitState();
      state = LOAD_GAME;
    }
  else if (button->getName() == "Settings")
    state = SETTINGS;
  else if (button->getName() == "ScoreButton")
    state = SCORE;
  else if (button->getName() == "KeyBoardConf")
    state = KEYBOARD_SETTINGS;
  else if (button->getName()[0] == '#')
  {
    lastButton = button->getCaption();
    state = GAME;
    deleteAllButton();
    resetInitState();
  }
  else if (button->getName() == "Human Count")
    {
      value = std::stoi((std::string)button->getCaption());
      button->setCaption(std::to_string((human = value == 2 ? 0 : (value + 1))));
    }
  else if (button->getName() == "IA Count")
    {
      value = std::stoi((std::string)button->getCaption());
      button->setCaption(std::to_string((ia = value == 2 ? 0 : (value + 1))));
    }
  else if (button->getName() == "Validation")
  {
    deleteAllButton();
    state = SELECT_CHAR;
    lastButton = "";
  }
  else if (button->getName() == "FullScreen Value")
    {
      button->setCaption(button->getCaption() == "No" ? "Yes" : "No");
      mcfg->setScreenValue(FULLSCREEN, button->getCaption());
    }
  else if (button->getName() == "Return")
    {
      deleteAllButton();
      resetInitState();
      state = GENERAL_MENU;
    }
  else if (button->getName() == "ReturnToSettings")
    {
      deleteAllButton();
      resetInitState();
      state = SETTINGS;
    }
  else if (button->getName() == "SaveConfig")
    {
      mcfg->saveFile(SCREEN, 0, 0);
      if (_player1 && _player2)
        mcfg->saveFile(KEYBOARD, _player1, _player2);
    }
  else if (button->getName() == "GoGame")
    {
      if (selectCharIdx == ia + human)
        state = GAME;
      else
      {
        if (state != SELECT_CHAR)
          deleteAllButton();
        resetInitState();
        state = SELECT_CHAR;
      }
    }
  else if (button->getName() == "playerClass")
    button->setCaption(button->getCaption() == "Lutin" ? "Warrior" : "Lutin");
  else if (button->getName() == "QuitButton")
    over = true;
}

MenuState
Menu::getMenuState() const
{
  return (state);
}

void
Menu::setMenuState(MenuState s)
{
  state = s;
}


void
Menu::resetInitState()
{
  for (int i = 0; i <= GAME; ++i)
  {
    initState[i] = false;
  }
}


bool
Menu::isInit(MenuState s) const
{
  return (initState[s]);
}

void
Menu::deleteAllButton(bool deleteHeroGuis)
{
  lastButtonPressed = 0;
  if (!deleteHeroGuis)
    mTrayMgr->destroyAllWidgetsInTray(OgreBites::TL_CENTER);
  else
    mTrayMgr->destroyAllWidgets();
  if (keyButton)
  {
    delete keyButton;
    keyButton = 0;
  }

  if (gameButton)
  {
    delete gameButton;
    gameButton = 0;
  }

  if (loadButton)
  {
    delete loadButton;
    loadButton = 0;
  }

  if (settingButton)
  {
    delete settingButton;
    settingButton = 0;
  }

  if (humanNumberButton)
  {
    delete humanNumberButton;
    humanNumberButton = 0;
  }

  if (fullScreenConfig)
  {
    delete fullScreenConfig;
    fullScreenConfig = 0;
  }

  if (returnButton)
  {
    delete returnButton;
    returnButton = 0;
  }

  if (iaNumberButton)
  {
    delete iaNumberButton;
    iaNumberButton = 0;
  }

  if (playerClass)
  {
    delete playerClass;
    playerClass = 0;
  }

  if (playerName)
  {
    delete playerName;
    playerName = 0;
  }


  if (!deleteHeroGuis || !heroGuis)
    return ;
  for (auto it = heroGuis->begin(); it != heroGuis->end();)
  {
    delete ((*it)->playername);
    delete ((*it)->bar);
    delete *it;
    it = heroGuis->erase(it);
  }
  heroGuis = 0;
}

void
Menu::createLoadMenu()
{
  DIR           *dp;
  struct dirent *ep;

  savedGames.clear();
  dp = opendir(SAVES_PATH);
  if (dp != NULL)
  {
    while (ep = readdir(dp))
    {
      if (ep->d_name[0] != '.')
        savedGames.push_back(mTrayMgr->createButton(OgreBites::TL_CENTER, "#Loaded Game: " + std::string(ep->d_name), std::string(ep->d_name), WIDTH_UI));
    }
    closedir(dp);
  }
  mTrayMgr->SdkTrayManager::createSeparator(OgreBites::TL_CENTER, "SeparatorReturn1", WIDTH_UI);
  returnButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "Return", "Revenir", WIDTH_UI);
  initState[LOAD_GAME] = true;
}

void
Menu::createScoreMenu(LeaderBoard *lb)
{
  const std::map<std::string, int> &scores = lb->getBoard();
  int i = 0;

  deleteAllButton();
  for (auto it = scores.begin(); it != scores.end(); ++it)
  {
    mTrayMgr->createButton(OgreBites::TL_CENTER, "ButtonScore" + std::to_string(i++), it->first + " : " + std::to_string(it->second), WIDTH_UI);
    if (i == 15)
      break ;
  }
  mTrayMgr->SdkTrayManager::createSeparator(OgreBites::TL_CENTER, "SeparatorReturn1", WIDTH_UI);
  returnButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "Return", "Revenir", WIDTH_UI);
  initState[SCORE] = true;
}

void
Menu::setInit(MenuState s) {
  initState[s] = true;
}

std::string
Menu::getLastButtonCaption()
{
  std::string ret = lastButton;

  lastButton = "";
  return (ret);
}

void
Menu::createChooseMenu()
{
  deleteAllButton();
  mTrayMgr->createButton(OgreBites::TL_CENTER, "Human Number :", "Human Number :", WIDTH_UI);
  humanNumberButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "Human Count", "0", WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "IA Number :", "IA Number :", WIDTH_UI);
  iaNumberButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "IA Count", "0", WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "Validation", "Go !", WIDTH_UI);
  mTrayMgr->SdkTrayManager::createSeparator(OgreBites::TL_CENTER, "SeparatorReturn2", WIDTH_UI);
  returnButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "Return", "Revenir", WIDTH_UI);
  initState[NEW_GAME] = true;
}

void
Menu::displayEndGame(std::string const &name, int score)
{
  deleteAllButton();
  mTrayMgr->showCursor();
  mTrayMgr->createButton(OgreBites::TL_CENTER, "DieButton", "Fin du jeu !", WIDTH_UI);
  mTrayMgr->SdkTrayManager::createSeparator(OgreBites::TL_CENTER, "SeparatorDieScreen", WIDTH_UI);
  returnButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "Return", "Revenir", WIDTH_UI);
  initState[DIE_SCREEN] = true;
}

void
Menu::getChars(int &nia, int &nhuman) const
{
  nhuman = (human == 0 && ia == 0 ? 1 : human);
  nia = ia;
}

void
Menu::createSettingsMenu(ConfigFileManager *cfg)
{
  mcfg = cfg;
  deleteAllButton();
  mTrayMgr->createButton(OgreBites::TL_CENTER, "Plein Ecran", "Plein Ecran ?", WIDTH_UI);
  humanNumberButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "FullScreen Value", cfg->getScreenValue(FULLSCREEN), WIDTH_UI);
  mTrayMgr->SdkTrayManager::createSeparator(OgreBites::TL_CENTER, "SeparatorReturn4", WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "KeyBoardConf", "Configuration du Clavier", WIDTH_UI);
  mTrayMgr->SdkTrayManager::createSeparator(OgreBites::TL_CENTER, "SeparatorReturn3", WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "SaveConfig", "Sauvegarder", WIDTH_UI);
  mTrayMgr->SdkTrayManager::createSeparator(OgreBites::TL_CENTER, "SeparatorReturn5", WIDTH_UI);
  returnButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "Return", "Revenir", WIDTH_UI);
  initState[SETTINGS] = true;
}

void
Menu::createKeyboardMenu(Keyboard *player1, Keyboard *player2, ConfigFileManager *cfm)
{
  _player1 = player1;
  _player2 = player2;
  deleteAllButton();
  mTrayMgr->createButton(OgreBites::TL_CENTER, "Player1Keyboard", "Player1", WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "p1Touch 1", "UP : " + cfm->getFromOIS(player1->getUp()), WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "p1Touch 2", "LEFT : " + cfm->getFromOIS(player1->getLeft()), WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "p1Touch 3", "DOWN : " + cfm->getFromOIS(player1->getDown()), WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "p1Touch 4", "RIGHT : " + cfm->getFromOIS(player1->getRight()), WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "p1Touch 5", "ATTACK : " + cfm->getFromOIS(player1->getAttack()), WIDTH_UI);
  mTrayMgr->SdkTrayManager::createSeparator(OgreBites::TL_CENTER, "SeparatorReturn6", WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "Player2Keyboard", "Player2", WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "p2Touch 1", "UP : " + cfm->getFromOIS(player2->getUp()), WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "p2Touch 2", "LEFT : " + cfm->getFromOIS(player2->getLeft()), WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "p2Touch 3", "DOWN : " + cfm->getFromOIS(player2->getDown()), WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "p2Touch 4", "RIGHT : " + cfm->getFromOIS(player2->getRight()), WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "p2Touch 5", "ATTACK : " + cfm->getFromOIS(player2->getAttack()), WIDTH_UI);
  mTrayMgr->SdkTrayManager::createSeparator(OgreBites::TL_CENTER, "SeparatorReturn7", WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "ReturnToSettings", "Revenir", WIDTH_UI);
  initState[KEYBOARD_SETTINGS] = true;
}

void
Menu::setInputValue(OIS::KeyCode code, ConfigFileManager *cfm, Keyboard *player1, Keyboard *player2)
{
  std::string pos;
  std::string value;
  Keyboard *player;

  if (lastButtonPressed && (lastButtonPressed->getName().find("p1Touch") != std::string::npos || lastButtonPressed->getName().find("p2Touch") != std::string::npos))
    {
      if (lastButtonPressed->getName().find("p1Touch") != std::string::npos)
        player = player1;
      else if (lastButtonPressed->getName().find("p2Touch") != std::string::npos)
        player = player2;
      pos = lastButtonPressed->getCaption();
      pos = pos.substr(0, pos.find(":") - 1);
      value = cfm->getFromOIS(code);
      if (pos == "UP")
        player->setUp(code);
      else if (pos == "RIGHT")
        player->setRight(code);
      else if (pos == "DOWN")
        player->setDown(code);
      else if (pos == "LEFT")
        player->setLeft(code);
      else if (pos == "ATTACK")
        player->setAttack(code);
      lastButtonPressed->setCaption(pos + " : " + value);
    }
}

void
Menu::setInputValue(OIS::KeyCode code, ConfigFileManager *cfm)
{
  if (code == OIS::KC_BACK)
    playerName->setCaption("");
  else
  {
    playerName->setCaption(playerName->getCaption() + cfm->getFromOIS(code));
    std::cout << "Apres le set caption" << std::endl;
  }
}

void
Menu::createSelectCharMenu(Game *game, EntitiesFactory *ef, Ogre::SceneManager *scene, Keyboard *player1, Keyboard *player2)
{
  std::string name;

  name = selectCharIdx < human ? "Player" : "IA";
  if (playerClass && playerName)
  {
    if (selectCharIdx <= human)
      game->addHero(playerName->getCaption(), playerClass->getCaption(), HUMAN, ef, scene, player1, player2, const_cast<Menu *>(this));
    else
      game->addHero(playerName->getCaption(), playerClass->getCaption(), COMPUTER, ef, scene, player1, player2, const_cast<Menu *>(this));
  }
  deleteAllButton(false);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "titlePlayerName", name + " " + std::to_string(selectCharIdx), WIDTH_UI);
  playerName = mTrayMgr->createButton(OgreBites::TL_CENTER, "playerName", name + std::to_string(selectCharIdx), WIDTH_UI);
  playerClass = mTrayMgr->createButton(OgreBites::TL_CENTER, "playerClass", "Lutin", WIDTH_UI);
  mTrayMgr->createButton(OgreBites::TL_CENTER, "GoGame", "OK", WIDTH_UI);
  ++selectCharIdx;
  setInit(SELECT_CHAR);
}

bool
Menu::isOver() const
{
  return (over);
}
