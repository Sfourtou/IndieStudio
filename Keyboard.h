#ifndef GAUNTLET_KEYBOARD_H
#define GAUNTLET_KEYBOARD_H


#include <OIS/OIS.h>

class       Keyboard {
    private:

    OIS::KeyCode    _up;
    OIS::KeyCode    _down;
    OIS::KeyCode    _right;
    OIS::KeyCode    _left;
    OIS::KeyCode    _attack;
    OIS::KeyCode    _save;
    OIS::KeyCode    _action;

public:
    Keyboard();
    ~Keyboard();
    void            setUp(OIS::KeyCode key);
    void            setDown(OIS::KeyCode key);
    void            setRight(OIS::KeyCode key);
    void            setLeft(OIS::KeyCode key);
    void            setAttack(OIS::KeyCode key);
    void            setAction(OIS::KeyCode key);
    OIS::KeyCode    getUp() const;
    OIS::KeyCode    getDown() const;
    OIS::KeyCode    getLeft() const;
    OIS::KeyCode    getRight() const;
    OIS::KeyCode    getAttack() const;
    OIS::KeyCode    getSave() const;
    OIS::KeyCode    getAction() const;

    Keyboard(OIS::KeyCode up, OIS::KeyCode down, OIS::KeyCode right, OIS::KeyCode left, OIS::KeyCode attack, OIS::KeyCode action = OIS::KC_RCONTROL);
};


#endif //GAUNTLET_KEYBOARD_H
