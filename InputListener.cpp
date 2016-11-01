#include "InputListener.h"

InputListener::InputListener(Ogre::RenderWindow *&window)
: mWindow(window), mCamera(0), yawValue(0), pitchValue(0)
{
    mRotate = 0.10;
    mCamNode = 0;
    mShutdown = false;
    initOIS();
}

InputListener::~InputListener() {
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
}

void InputListener::initSceneMgr(Ogre::SceneManager  * &sceneMgr)
{
    mSceneMgr = sceneMgr;
    //Debut loading
    game.loadEverything(mSceneMgr);
    //Fin l     oading
    mCollisionManager = new MOC::CollisionTools(mSceneMgr);
    menu = new Menu(mSceneMgr, mMouse, mKeyboard, mWindow, const_cast<InputListener *>(this));
}

void InputListener::initOIS()
{
    Ogre::LogManager::getSingleton().logMessage("Initializing OIS");
    OIS::ParamList pl;
    std::ostringstream windowHndStr;

    size_t windowsHnd = 0;

    mWindow->getCustomAttribute("WINDOW", &windowsHnd);
    windowHndStr << windowsHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    mInputManager = OIS::InputManager::createInputSystem(pl);
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
    OIS::MouseState &mutableMouseState = const_cast<OIS::MouseState &>(mMouse->getMouseState());
    mutableMouseState.Y.abs = (mWindow->getHeight() / 2) - (mWindow->getHeight() / 10);
    mutableMouseState.X.abs = mWindow->getWidth() / 2;
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
    windowResized(mWindow);
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);
    lb.loadScore();
    cfm.readFile(SCREEN, "./ogre.cfg", 0, 0);
    cfm.readFile(KEYBOARD, "./keyboard.cfg", &player1, &player2);
}

bool InputListener::frameRenderingQueued(const Ogre::FrameEvent &event) {
    globalKeyCount = 0;
    if (mWindow->isClosed())
        return false;
    mKeyboard->capture();
    mMouse->capture();
    if (mShutdown || menu->isOver() == true)
        return false;
    switch (menu->getMenuState())
    {
      case SPLASHSCREEN:
      {
          displaySplashscreen();
        break ;
      }
      case GENERAL_MENU:
      {
        displayGeneralMenu();
        break ;
      }
      case SCORE:
      {
        displayScoreMenu();
        break ;
      }
      case SETTINGS:
      {
        displaySettings();
        break ;
      }
      case KEYBOARD_SETTINGS:
      {
        displayKeyboardSettings();
        break ;
      }
      case NEW_GAME:
      {
        displayNewGame();
        break ;
      }
      case LOAD_GAME:
      {
        displayLoadGame();
        break ;
      }
      case SELECT_CHAR:
      {
        displaySelectChar();
        break ;
      }
      case DIE_SCREEN:
      {
        displayDieScreen();
        break ;
      }
      case GAME:
      {
        displayGame(event, globalKeyCount);
        break ;
      }
    }
    return true;
}

void InputListener::windowResized(Ogre::RenderWindow *window)
{
    unsigned int width, height, depth;
    int left, top;
    window->getMetrics(width, height, depth, left, top);
    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

void    InputListener::windowClosed(Ogre::RenderWindow *window)
{
    if (window == mWindow)
    {
        if (mInputManager)
        {
            mInputManager->destroyInputObject(mMouse);
            mInputManager->destroyInputObject(mKeyboard);
            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}

bool InputListener::mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID id) {
    if (menu)
      menu->getTrayMgr()->injectPointerDown(me, id);
    return false;
}


bool InputListener::mouseMoved(const OIS::MouseEvent &me)
{
  if (menu)
    menu->getTrayMgr()->injectPointerMove(me);
   if (mCamNode)
    {
      yawValue += -mRotate * me.state.X.rel;
      pitchValue += -mRotate * me.state.Y.rel;
      mCamNode->yaw(Ogre::Degree(-mRotate * me.state.X.rel), Ogre::Node::TS_WORLD);
      mCamNode->pitch(Ogre::Degree(-mRotate * me.state.Y.rel), Ogre::Node::TS_LOCAL);
    }
}

bool InputListener::mouseReleased(const OIS::MouseEvent &me, OIS::MouseButtonID id) {
  if (menu)
    menu->getTrayMgr()->injectPointerUp(me, id);
    return false;
}

bool InputListener::keyPressed(const OIS::KeyEvent &ke) {
    if (ke.key == OIS::KC_ESCAPE)
        mShutdown = true;
    if (menu->getMenuState() == KEYBOARD_SETTINGS)
      {
        menu->setInputValue(ke.key, &cfm, &player1, &player2);
        return true;
      }
    if (menu->getMenuState() == SELECT_CHAR)
      {
        menu->setInputValue(ke.key, &cfm);
        return true;
      }
    for(int i = 0; i < game.getHeros()->size(); ++i)
    {
        Keyboard *key;
        if ((key = game.getHero(i)->getKey()) != NULL)
        {
	  if (ke.key == key->getUp())
	    game.getHero(i)->setDir(game.getHero(i)->getDir() - Ogre::Vector3::UNIT_Z);
	  if (ke.key == key->getDown())
	    game.getHero(i)->setDir(game.getHero(i)->getDir() + Ogre::Vector3::UNIT_Z);
	  if (ke.key == key->getRight())
	    game.getHero(i)->setDir(game.getHero(i)->getDir() + Ogre::Vector3::UNIT_X);
	  if (ke.key == key->getLeft())
	    game.getHero(i)->setDir(game.getHero(i)->getDir() - Ogre::Vector3::UNIT_X);
            if (ke.key == key->getAction())
                game.openTheDoor(mSceneMgr, game.getHero(i), 1);
	  if (game.getHero(i)->getDir() != Ogre::Vector3::ZERO)
	    game.getHero(i)->setLastDir(game.getHero(i)->getDir());
        }
    }
     if (ke.key == OIS::KC_Q)
     {
         //std::cout << game.getHero(0)->getPosition() << std::endl;
     }
    return true;
}

bool InputListener::keyReleased(const OIS::KeyEvent &ke) {
    for(int i = 0; i < game.getHeros()->size(); ++i)
    {
        Keyboard *key;
        if ((key = game.getHero(i)->getKey()) != NULL)
        {
            if (ke.key == key->getUp())
                game.getHero(i)->setDir(game.getHero(i)->getDir() + Ogre::Vector3::UNIT_Z);
            if (ke.key == key->getDown())
                game.getHero(i)->setDir(game.getHero(i)->getDir() - Ogre::Vector3::UNIT_Z);
            if (ke.key == key->getRight())
                game.getHero(i)->setDir(game.getHero(i)->getDir() - Ogre::Vector3::UNIT_X);
            if (ke.key == key->getLeft())
                game.getHero(i)->setDir(game.getHero(i)->getDir() + Ogre::Vector3::UNIT_X);
            if (ke.key == key->getAttack()) {
                game.getHero(i)->setIsAttacking(true);
            }
            if (game.getHero(i)->getDir() != Ogre::Vector3::ZERO)
                game.getHero(i)->setLastDir(game.getHero(i)->getDir());
        }
    }
    if (ke.key == player1.getSave() && game.dragonIsAlive() == true)
        ds.saveGame(game.getEnnemies(), *game.getHeros(), game.getDrops(), game.getSpawners(), game.getProjectiles(), game.getScore(), game.getZones(), game.getIdx());
    return true;
}

void
InputListener::createCamera()
{
    mCamera = mSceneMgr->createCamera("MainCamera");
    mCamera->setPosition(0, 0, 0);
    mCamera->lookAt(0, 0, 0);
    mCamera->setNearClipDistance(1);
    //mCamera->setFarClipDistance(100);
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
    mCamera->setAspectRatio(
            Ogre::Real(vp->getActualWidth()) /
            Ogre::Real(vp->getActualHeight()));
}

void	music(irrklang::ISoundEngine *engine)
{
  engine->play2D("../sound/music_mono.wav", true);
}

void
InputListener::setScene()
{
    Ogre::Entity* map = mSceneMgr->createEntity("map", "newmap.mesh");
    Ogre::Entity* door = mSceneMgr->createEntity("Doors.mesh");
    Ogre::Entity* door1 = mSceneMgr->createEntity("Doors.001.mesh");
    Ogre::Entity* door2 = mSceneMgr->createEntity("Doors.002.mesh");
    Ogre::Entity* door3 = mSceneMgr->createEntity("Doors.003.mesh");
    Ogre::Entity* door4 = mSceneMgr->createEntity("Doors.004.mesh");
    Ogre::Entity* door5 = mSceneMgr->createEntity("Doors.005.mesh");
    Ogre::Entity* door6 = mSceneMgr->createEntity("Doors.006.mesh");
    Ogre::Entity* door7 = mSceneMgr->createEntity("Doors.007.mesh");
    Ogre::Entity* door8 = mSceneMgr->createEntity("Doors.008.mesh");
    Ogre::Entity* goldChest = mSceneMgr->createEntity("goldChest.mesh");

    map->setQueryFlags(MAP);
    game.setSceneManager(mSceneMgr);
    Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("map1");
    Ogre::SceneNode* DoorsNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("doors");
    Ogre::SceneNode* DoorsNode1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("doors1");
    Ogre::SceneNode* DoorsNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode("doors2");
    Ogre::SceneNode* DoorsNode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode("doors3");
    Ogre::SceneNode* DoorsNode4 = mSceneMgr->getRootSceneNode()->createChildSceneNode("doors4");
    Ogre::SceneNode* DoorsNode5 = mSceneMgr->getRootSceneNode()->createChildSceneNode("doors5");
    Ogre::SceneNode* DoorsNode6 = mSceneMgr->getRootSceneNode()->createChildSceneNode("doors6");
    Ogre::SceneNode* DoorsNode7 = mSceneMgr->getRootSceneNode()->createChildSceneNode("doors7");
    Ogre::SceneNode* DoorsNode8 = mSceneMgr->getRootSceneNode()->createChildSceneNode("doors8");
    Ogre::SceneNode* GoldChest = mSceneMgr->getRootSceneNode()->createChildSceneNode("goldchest");
    ogreNode->attachObject(map);
    DoorsNode->attachObject(door);
    DoorsNode1->attachObject(door1);
    DoorsNode2->attachObject(door2);
    DoorsNode3->attachObject(door3);
    DoorsNode4->attachObject(door4);
    DoorsNode5->attachObject(door5);
    DoorsNode6->attachObject(door6);
    DoorsNode7->attachObject(door7);
    DoorsNode8->attachObject(door8);
    GoldChest->attachObject(goldChest);
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
    GoldChest->setScale(1.5, 1.5, 1.5);
    GoldChest->setPosition(-55, -86, -140);
   Ogre::Quaternion q(Ogre::Degree(90), Ogre::Vector3::UNIT_Y);
    GoldChest->rotate(q);
    game.addDoor(DoorsNode);
    game.addDoor(DoorsNode6);
    game.addDoor(DoorsNode5);
    game.addDoor(DoorsNode4);
    game.addDoor(DoorsNode3);
    game.addDoor(DoorsNode2);
    game.addDoor(DoorsNode1);
    game.addDoor(DoorsNode7);
    game.addDoor(DoorsNode8);
    ogreNode->setPosition(0, -100, 0);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(0, 100, 0);
    game.engine = irrklang::createIrrKlangDevice();
    game.bossTime(mSceneMgr);
    std::thread(music, game.engine).detach();
}

int g_slider_position = 0;
CvCapture *g_capture = NULL;

void onTrackbarSlide(int pos)
{
  cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, pos);
}

void doSplashscreen()
{
  cvNamedWindow( "../splashscreen/SPLASHSCREEN.mp4", CV_WINDOW_AUTOSIZE );
  g_capture = cvCreateFileCapture( "../splashscreen/SPLASHSCREEN.mp4" );
  int frames = (int) cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_COUNT);

  IplImage* frame;
  while(g_slider_position != 150)
    {
      frame = cvQueryFrame( g_capture );
      if( !frame ) break;
           cvShowImage( "GAUTLET by LEGEND", frame );
      std::cout << g_slider_position << std::endl;
      char c = cvWaitKey('q');
      if( c == 'q')
        break;
    }
    cvReleaseCapture( &g_capture );
    cvDestroyWindow( "../splashscreen/SPLASHSCREEN.mp4" );
    exit (0);
}

void
InputListener::displaySplashscreen()
{
  int pid;

  if (!menu->isInit(SPLASHSCREEN))
  {
   if ((pid = fork()) == 0)
     doSplashscreen();
    menu->setInit(SPLASHSCREEN);
    menu->setMenuState(GENERAL_MENU);
  }
  else
  {

  }
}

void
InputListener::displayGeneralMenu()
{
  if (!menu->isInit(GENERAL_MENU))
  {
    if (!mCamNode)
    {
      setScene();
      mCamNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode0", START_POSITION + Ogre::Vector3(5, 40, 30));
      mCamNode->yaw(Ogre::Degree(0));
      mCamNode->lookAt(Ogre::Vector3(0, -60, 0), Ogre::Node::TS_WORLD);
      mCamNode->attachObject(mCamera);
    }
    menu->createLaunchMenu();
  }
  else
  {
  }
}

void
InputListener::displaySettings()
{
  if (!menu->isInit(SETTINGS))
    menu->createSettingsMenu(&cfm);
  else
  {

  }
}

void
InputListener::displayKeyboardSettings()
{
  if (!menu->isInit(KEYBOARD_SETTINGS))
    menu->createKeyboardMenu(&player1, &player2, &cfm);
  else
    {

    }
}


void
InputListener::displayNewGame()
{
  if (!menu->isInit(NEW_GAME))
    menu->createChooseMenu();
  else
  {

  }
}

void
InputListener::displayLoadGame()
{
  if (!menu->isInit(LOAD_GAME))
  {
    menu->createLoadMenu();
  }
  else
  {

  }
}

void
InputListener::displayScoreMenu()
{
  if (!menu->isInit(SCORE))
  {
    menu->createScoreMenu(&lb);
  }
  else
  {

  }
}

void
InputListener::displaySelectChar()
{
  if (!menu->isInit(SELECT_CHAR))
  {
    menu->createSelectCharMenu(&game, &ef, mSceneMgr, &player1, &player2);
  }
  else
  {

  }
}

void
InputListener::displayDieScreen()
{
  if (!menu->isInit(DIE_SCREEN))
  {
    menu->displayEndGame(game.getOwner(), game.getScore());
  }
  else
  {

  }
}

void
InputListener::displayGame(const Ogre::FrameEvent &event, int &globalKeyCount)
{
  std::string gameFile;

  if (!menu->isInit(GAME))
  {
    menu->createSelectCharMenu(&game, &ef, mSceneMgr, &player1, &player2);
    menu->deleteAllButton(false);
    menu->getTrayMgr()->hideCursor();
    menu->createKeyGUI();
    menu->createScoreGUI();
    if ((gameFile = menu->getLastButtonCaption()) != "")
      ds.loadGame(&game, gameFile, &ef, mSceneMgr, menu, &player1, &player2);
    else
      game.initGame(menu, &ef, mSceneMgr, &player1, &player2);
      mCamNode->resetToInitialState();
      int hero;
      if ((hero = game.getHuman()) == -1)
          hero = 0;
      mCamNode->setPosition(game.getHero(hero)->getPosition() + Ogre::Vector3(5, 40, 30));
      mCamNode->lookAt(game.getHero(hero)->getPosition(), Ogre::Node::TS_WORLD);
    menu->setInit(GAME);
  }
  else {
      game.moveAi(mCollisionManager, event, mSceneMgr, globalKeyCount);

      if (game.bossIsEnabled()) {
          if (game.moveCamera()) {
              game.setMoveCamera(false);
              mCamNode->translate(Ogre::Vector3(0, 5, 0));
          }
          game.bossPattern(mSceneMgr, event);
      }
      game.moveObjects(event);
      game.moveEnemies(mSceneMgr, mCollisionManager, event, mSceneMgr);

      game.attack(mSceneMgr, event);
      if (game.moveHeros(mCollisionManager, event, mCamNode, globalKeyCount, true, mSceneMgr, menu))
      game.checkDrop(mSceneMgr, menu);

    game.spawnEnnemies(mSceneMgr, &ef, event);
    game.moveProjectile(mCollisionManager, event.timeSinceLastFrame, mSceneMgr);
    game.dropsLoop();
    if (game.checkEnd())
    {
      lb.addScore(game.getOwner(), game.getScore());
      lb.saveScore();
      game.clearResources(mSceneMgr);
      menu->resetInitState();
      menu->setMenuState(DIE_SCREEN);
    }
    else
    {
      menu->updateKeyGUI(globalKeyCount);
      menu->updateScoreGUI(game.getScore());
    }
  }
}
