cmake_minimum_required(VERSION 2.8)
project(Gauntlet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(UNIX)
    if(EXISTS "/usr/local/lib/OGRE/cmake")

        set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
        set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local

    elseif(EXISTS "/usr/lib/OGRE/cmake")

        set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
        set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/") # Otherwise, this one

    else ()
        message(SEND_ERROR "Failed to find module path.")
    endif(EXISTS "/usr/local/lib/OGRE")
endif(UNIX)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}")

find_package(OGRE REQUIRED)
if (NOT OGRE_FOUND)
    message(SEND_ERROR "Failer to fin ogre.")
        endif()

find_package(OIS REQUIRED)
if(NOT OIS_FOUND)
    message(SEND_ERROR "Failed to find OIS.")
endif()

if (NOT OGRE_BUILD_PLATFORM_IPHONE)
    if (WIN32 OR APPLE)
        set(Boost_USE_STATIC_LIBS TRUE)
    else ()
        # Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
        set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
    endif ()
    if (MINGW)
        # this is probably a bug in CMake: the boost find module tries to look for
        # boost libraries with name libboost_*, but CMake already prefixes library
        # search names with "lib". This is the workaround.
        set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
    endif ()
    set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
    # Components that need linking (NB does not include header-only components like bind)
    set(OGRE_BOOST_COMPONENTS thread date_time)
    find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
    if (NOT Boost_FOUND)
        # Try again with the other type of libs
        set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
        find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
    endif()
    find_package(Boost QUIET)

    # Set up referencing of Boost
    include_directories(${Boost_INCLUDE_DIR})
    add_definitions(-DBOOST_ALL_NO_LIB)
    set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
endif()

find_package(OpenCV REQUIRED)

include_directories( ${OIS_INCLUDE_DIRS}
        ${OGRE_INCLUDE_DIRS}
        ${OGRE_SAMPLES_INCLUDEPATH}
        ${OGRE_Overlay_INCLUDE_DIRS}
        )

link_directories(${CMAKE_BINARY_DIR})
set(SOURCE_FILES main.cpp CoreApplication.cpp CoreApplication.h InputListener.cpp InputListener.h CollisionTools.cpp CollisionTools.h Entities/ACharacter.cpp Entities/ACharacter.h Entities/Archer.h Entities/Archer.cpp Entities/EntitiesFactory.cpp Entities/EntitiesFactory.h Entities/Ghost.cpp Entities/Ghost.h Entities/Grunt.cpp Entities/Grunt.h Game.cpp Entities/Spawner.cpp Key.cpp Timer.cpp Potion.cpp AItem.cpp Projectile.cpp Keyboard.cpp Keyboard.h Zone.cpp Zone.h Menu.cpp Menu.hh DataSerialize.cpp DataSerialize.h Entities/AHero.cpp Entities/AHero.h MoveUtils.cpp MoveUtils.h DamagePowerUp.cpp DamagePowerUp.h SpeedPowerUp.cpp SpeedPowerUp.h APowerUp.cpp APowerUp.h Entities/Demon.cpp Entities/Demon.h Entities/Warrior.cpp Entities/Warrior.h ConfigFileManager.cpp Entities/Dragon.cpp Entities/Dragon.h LeaderBoard.cpp LeaderBoard.h)
add_executable(Gauntlet ${SOURCE_FILES})
target_link_libraries(Gauntlet /home/marcha_0/Rendu/cpp_indie_studio/libIrrKlang.so ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${OGRE_Overlay_LIBRARIES} ${OpenCV_LIBS})
