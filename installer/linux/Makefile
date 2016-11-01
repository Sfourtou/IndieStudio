##
## Makefile for  in /home/marcha_0/Rendu/cpp_indie_studio/installer/linux
## 
## Made by marcha_0
## Login   <marcha_0@epitech.net>
## 
## Started on  Thu Jun  9 01:39:29 2016 marcha_0
## Last update Thu Jun  9 01:53:13 2016 marcha_0
##

CP	= cp

DIR_TARGET = /opt/gauntlet

DIR_OGRE_LIB = /usr/local/lib/

install:
	$(CP) ./dep/*.so* /usr/lib/
	mkdir -p $(DIR_TARGET)
	$(CP) -rf bin $(DIR_TARGET)
	$(CP) -rf media $(DIR_TARGET)
	$(CP) -rf sound $(DIR_TARGET)
	$(CP) -rf splashscreen $(DIR_TARGET)
	$(CP) -rf dep/OGRE $(DIR_OGRE_LIB)
	$(CP) -rf gauntlet /usr/bin
