#include "CoreApplication.h"
#include "InputListener.h"

CoreApplication::CoreApplication() :
mRoot(0),
mResourcesCfg(Ogre::BLANKSTRING),
mPluginsCfg(Ogre::BLANKSTRING)
{

}

CoreApplication::~CoreApplication() {
    delete mRoot;
}

void CoreApplication::parseConfigFile()
{
    Ogre::String name, locType;
    Ogre::ConfigFile::SectionIterator sectionIterator = cf.getSectionIterator();

    while (sectionIterator.hasMoreElements())
    {
        Ogre::ConfigFile::SettingsMultiMap *settingsMultiMap = sectionIterator.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator it;
        for(it = settingsMultiMap->begin(); it != settingsMultiMap->end(); ++it)
        {
            locType = it->first;
            name = it->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
        }
    }
}

bool CoreApplication::configRenderSystem()
{
    if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
        return false;
};

void CoreApplication::createCamera()
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

void    CoreApplication::setScene()
{

  Ogre::Entity* map = mSceneMgr->createEntity("map", "newmap.mesh");
  map->setQueryFlags(MAP);
  Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("map1");
  //ogreNode->attachObject(map);
  ogreNode->setPosition(0, -100, 0);

    Ogre::Entity *entity = mSceneMgr->createEntity("Doors.mesh");
    //ogreNode->attachObject(entity);
    //Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("doors", Ogre::Vector3(0, -100 , 0));
    //node->attachObject(entity);

  mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

  Ogre::Light* light = mSceneMgr->createLight("MainLight");
  light->setPosition(0, 100, 0);
}

void CoreApplication::createFrameListener()
{
    mInputListener = new InputListener(mWindow);
    mRoot->addFrameListener(mInputListener);
    mInputListener->initSceneMgr(mSceneMgr);
    mInputListener->createCamera();
}

bool CoreApplication::setConfig() {
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";

    mRoot = new Ogre::Root(mPluginsCfg);
    cf.load(mResourcesCfg);
    parseConfigFile();
    configRenderSystem();
    //if (configRenderSystem() == false)
      //  return false;
    createWindow();
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
    // createCamera();
    // setScene();
    createFrameListener();
    mRoot->startRendering();
   // while (true) {
    //    Ogre::WindowEventUtilities::messagePump();
    //}
}

void CoreApplication::createWindow() {
    mWindow = mRoot->initialise(true, "Gauntlet");
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
