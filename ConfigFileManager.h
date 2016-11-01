#ifndef CFM_H_
# define CFM_H_
# include <map>
# include <fstream>
# include <iostream>
# include <string>
# include "Keyboard.h"
# define RENDER_SYSTEM "Render System"
# define COLOUR_DEPTH "Colour Depth"
# define DISPLAY_FREQUENCY "Display Frequency"
# define FSAA "FSAA"
# define FPE "Fixed Pipeline Enabled"
# define FULLSCREEN "Full Screen"
# define RTT "RTT Preferred Mode"
# define VSYNC "VSync"
# define VIDEO_MODE "Video Mode"
# define SRGB "sRGB Gamma Conversion"
# define OGRE_CONFIG "./ogre.cfg"
# define KEYBOARD_CONFIG "./keyboard.cfg"

enum FileType
{
  SCREEN,
  KEYBOARD
};

class ConfigFileManager
{
public:
  ConfigFileManager();
  ~ConfigFileManager();
  void readFile(FileType type, std::string const &path, Keyboard *p1, Keyboard *p2);
  void updateFile(FileType type, std::string const &name, std::string const &value);
  void saveFile(FileType type, Keyboard *, Keyboard *) const;
  std::string const &getScreenValue(std::string const &value) const;
  void setScreenValue(std::string const &key, std::string const &value);
  std::string getFromOIS(OIS::KeyCode) const;
private:
  void saveScreen() const;
  void saveKeyboard(Keyboard *, Keyboard *) const;
  void updateScreen(std::string const &name, std::string const &value);
  void updateKeyboard(std::string const &name, std::string const &value);
  void readScreenFile(std::string const &path);
  void readKeyboardFile(std::string const &path, Keyboard *p1, Keyboard *p2);
  void setKeyboardTouch(Keyboard *currentPlayer, std::string touch, int i);
  std::map<std::string, std::string> ogreConf;
  std::map<std::string, std::string> keyboardConf;
  std::string keyboardPath;
  std::string screenPath;
  std::map<std::string, OIS::KeyCode> keys;
};

#endif
