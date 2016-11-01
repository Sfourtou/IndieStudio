#ifndef GAUNTLET_COREAPPLICATION_H
#define GAUNTLET_COREAPPLICATION_H

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreConfigFile.h>
#include <OGRE/OgreRenderSystem.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreTextureManager.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreCamera.h>
#include <OGRE/OgreViewport.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreWindowEventUtilities.h>
#include "InputListener.h"

class CoreApplication
{
private:
    Ogre::Root          *mRoot;
    Ogre::String        mResourcesCfg;
    Ogre::String        mPluginsCfg;
    Ogre::ConfigFile    cf;
    Ogre::RenderWindow  *mWindow;
    Ogre::SceneManager  *mSceneMgr;
    Ogre::Camera        *mCamera;
    InputListener *mInputListener;
    Ogre::SceneNode *mArcherNode;
    Ogre::Entity * mArcher;
    Ogre::AnimationState * mAnimationState;

public:
    CoreApplication();
    void    createWindow();
    virtual ~CoreApplication();
    bool    setConfig();
    void    parseConfigFile();
    bool    configRenderSystem();
    void    createCamera();
    void    setScene();
    void    createFrameListener();
};


#endif //GAUNTLET_COREAPPLICATION_H
