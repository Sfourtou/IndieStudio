#ifndef GAUNTLET_INPUTLISTENER_H
#define GAUNTLET_INPUTLISTENER_H

#include <OGRE/Ogre.h>
#include <OGRE/SdkTrays.h>
#include <OIS/OIS.h>
#include "Scene.h"
#include "Camera.h"
#include "CollisionTools.h"
#include "Entities/EntitiesFactory.h"
#include "Entities/ACharacter.h"
#include "Entities/Spawner.h"
#include "ConfigFileManager.h"
#include "Game.h"
#include "Projectile.h"
#include "Keyboard.h"
#include "Menu.hh"
#include "DataSerialize.h"
#include "LeaderBoard.h"

enum MASK{
    PERSO = 1 << 0,
    MAP   = 1 << 1,
};

class InputListener : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::MouseListener, public OIS::KeyListener, public OgreBites::SdkTrayListener {

private:
        Ogre::RenderWindow  *mWindow;
        Ogre::Camera        *mCamera;
        OIS::InputManager   *mInputManager;
        OIS::Mouse          *mMouse;
        OIS::Keyboard       *mKeyboard;
        MOC::CollisionTools *mCollisionManager;
        Game                 game;
        EntitiesFactory      ef;
        Keyboard             player1;
        Keyboard             player2;
        Menu                  *menu;
        DataSerialize         ds;
        ConfigFileManager     cfm;
        LeaderBoard           lb;
        float yawValue;
        float pitchValue;
public:
    InputListener(Ogre::RenderWindow * &window);
    ~InputListener();
    bool frameRenderingQueued(const Ogre::FrameEvent &event);
    void initOIS();
    virtual void windowResized(Ogre::RenderWindow * rw);
    virtual void windowClosed(Ogre::RenderWindow *rw);
    virtual bool mouseMoved(const OIS::MouseEvent &me);
    virtual bool mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &me, OIS::MouseButtonID id);
    virtual bool keyPressed(const OIS::KeyEvent& ke);
    virtual bool keyReleased(const OIS::KeyEvent& ke);
    void    createCamera();
    void    setScene();
    void    initSceneMgr(Ogre::SceneManager *&mSceneMgr);

    Ogre::Real mRotate;
    Ogre::SceneNode *mCamNode;
    bool        mShutdown;
    Ogre::SceneManager *mSceneMgr;
private:
  void displaySplashscreen();
  void displayGeneralMenu();
  void displaySettings();
  void displayKeyboardSettings();
  void displayLoadGame();
  void displayScoreMenu();
  void displayNewGame();
  void displayGame(const Ogre::FrameEvent &event, int &globalKeyCount);
  void displaySelectChar();
  void displayDieScreen();
  int globalKeyCount;
};

#endif //GAUNTLET_INPUTLISTENER_H
