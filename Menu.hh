#ifndef MENU_HH_
# define MENU_HH_
# define RESOURCE_GROUP_FRAMEWORK "Overlay"
# define TRAY_MAANGR_NAME "TrayManager"
# define WIDTH_UI 400

#include <OGRE/Ogre.h>
#include <OGRE/SdkTrays.h>
#include <OIS/OIS.h>
#include "cv.h"
#include "highgui.h"
#include "ConfigFileManager.h"
#include "LeaderBoard.h"
#include "sound/include/irrKlang.h"

class Game;
class InputListener;
class EntitiesFactory;

enum MenuState
{
  SPLASHSCREEN,
  GENERAL_MENU,
  SETTINGS,
  SCORE,
  KEYBOARD_SETTINGS,
  NEW_GAME,
  LOAD_GAME,
  SELECT_CHAR,
  DIE_SCREEN,
  GAME
};

struct guiHero
{
  OgreBites::Button      *playername;
  OgreBites::ProgressBar *bar;
};

class Menu : public OgreBites::SdkTrayListener
{
public:
  Menu(Ogre::SceneManager *mSceneMgr, OIS::Mouse *mMouse, OIS::Keyboard *mKeyboard, Ogre::RenderWindow *mWindow, InputListener *il);
  ~Menu();
  void createLaunchMenu();
  void createKeyGUI();
  void updateKeyGUI(int keyNumber);
  void createScoreGUI();
  void updateScoreGUI(int newScore);
  guiHero *createHeroGui(std::string const &playerName, int life, int maxLife);
  guiHero *createDragonGui(std::string const &playerName, int life, int maxLife);
  OgreBites::SdkTrayManager *getTrayMgr() const;
  void buttonHit(OgreBites::Button *button);
  MenuState getMenuState() const;
  void setMenuState(MenuState);
  void createLoadMenu();
  bool isInit(MenuState) const;
  void setInit(MenuState menu);
  std::string getLastButtonCaption();
  void createChooseMenu();
  void createScoreMenu(LeaderBoard *);
  void createSettingsMenu(ConfigFileManager *cfg);
  void createKeyboardMenu(Keyboard *player1, Keyboard *player2, ConfigFileManager *cfm);
  void createSelectCharMenu(Game *game, EntitiesFactory *ef, Ogre::SceneManager *scene, Keyboard *player1, Keyboard *player2);
  void getChars(int &, int &) const;
  void                        deleteAllButton(bool deleteHeroGuis = true);
  void setInputValue(OIS::KeyCode code, ConfigFileManager *cfm, Keyboard *player1, Keyboard *player2);
  void setInputValue(OIS::KeyCode code, ConfigFileManager *cfm);
  void                        resetInitState();
  void                        displayEndGame(std::string const &name, int score);
  bool isOver() const;
private:
  bool over;
  Ogre::OverlaySystem         *mOverlaySystem;
  OgreBites::SdkTrayManager   *mTrayMgr;
  OgreBites::Button           *keyButton;
  OgreBites::Button           *scoreButton;
  std::vector<guiHero *>      *heroGuis;
  OgreBites::Button           *gameButton;
  OgreBites::Button           *loadButton;
  OgreBites::Button           *settingButton;

  OgreBites::Button           *humanNumberButton;
  OgreBites::Button           *iaNumberButton;
  int                          ia;
  int                          human;

  OgreBites::Button           *fullScreenConfig;
  OgreBites::Button           *returnButton;

  OgreBites::Button           *playerClass;
  OgreBites::Button           *playerName;

  std::vector<OgreBites::Button *> savedGames;
  MenuState                   state;
  bool                         initState[GAME + 1];
  std::string                 lastButton;
  ConfigFileManager           *mcfg;
  OgreBites::Button           *lastButtonPressed;
  Keyboard *_player1;
  Keyboard *_player2;
  int selectCharIdx;
  irrklang::ISoundEngine *engine;
};

#endif /* MENU_HH_ */
