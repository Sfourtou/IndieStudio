#ifndef SCENE_H_
# define SCENE_H_
#include <OGRE/Ogre.h>
#include <OIS/OIS.h>
#include <map>

class Scene
{
public:
  Scene();
  ~Scene();
  void addNode(void *, Ogre::SceneNode *);
  void deleteNode(void *);
  void setSceneMgr(Ogre::SceneManager *&scene);
  Ogre::SceneManager *getSceneMgr() const;
  Ogre::Entity *createEntity(const std::string &name, const std::string &mesh);
  Ogre::SceneNode *createNode(const std::string &name, Ogre::Vector3 vector);
  Ogre::SceneManager * getSceneManager() const;
private:
  Ogre::SceneManager *mSceneMgr;
  std::map<void *, Ogre::SceneNode *> nodes;
};

#endif
