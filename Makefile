## marcha triple pute

NAME	= ./bin/gauntlet

CC 	= g++

RM	= rm -f

SRC	= CoreApplication.cpp		\
	InputListener.cpp		\
	main.cpp			\
	Camera.cpp			\
	LeaderBoard.cpp			\
	CollisionTools.cpp		\
	DataSerialize.cpp		\
	Menu.cpp			\
	Game.cpp			\
	Entities/ACharacter.cpp 	\
	Entities/AHero.cpp	 	\
	Entities/Archer.cpp		\
	Entities/EntitiesFactory.cpp	\
	Entities/Ghost.cpp		\
	Entities/Spawner.cpp		\
	Entities/Grunt.cpp		\
	Entities/Warrior.cpp		\
	Entities/Demon.cpp		\
	Entities/Dragon.cpp		\
	AItem.cpp			\
	Potion.cpp			\
	Key.cpp				\
	Timer.cpp			\
	Projectile.cpp			\
	Keyboard.cpp			\
	Zone.cpp			\
	MoveUtils.cpp			\
	SpeedPowerUp.cpp		\
	DamagePowerUp.cpp		\
	ConfigFileManager.cpp		\
	APowerUp.cpp

OBJ	= $(SRC:.cpp=.o)

LIB	= -I/usr/local/include/OGRE `pkg-config --libs OGRE` -I/usr/include/OIS -I/usr/include/opencv -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_stitching -lOIS -lboost_system -std=c++11 -L/usr/local/lib/OGRE -lOgreOverlay -lOgreMain -lpthread -L"/usr/lib" -L. -lIrrKlang

CXXFLAGS = -std=c++11 -I/usr/local/include/OGRE/Overlay -I/usr/local/include/OGRE/ -I/usr/include/OIS -I/usr/include/opencv -I"/sound/include" -O3

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIB)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
