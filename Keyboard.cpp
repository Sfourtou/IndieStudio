#include "Keyboard.h"

Keyboard::Keyboard()
: _up(OIS::KC_W), _down(OIS::KC_S), _right(OIS::KC_D), _left(OIS::KC_A), _attack(OIS::KC_LSHIFT), _save(OIS::KC_P), _action(OIS::KC_E)
{

}

Keyboard::Keyboard(OIS::KeyCode up, OIS::KeyCode down, OIS::KeyCode right, OIS::KeyCode left, OIS::KeyCode attack, OIS::KeyCode action)
: _up(up), _down(down), _right(right), _left(left), _attack(attack), _save(OIS::KC_P), _action(action)
{
}

void Keyboard::setUp(OIS::KeyCode key) {
    _up = key;
}

void Keyboard::setDown(OIS::KeyCode key) {
    _down = key;
}

void Keyboard::setRight(OIS::KeyCode key) {
    _right = key;
}

void Keyboard::setLeft(OIS::KeyCode key) {
    _left = key;
}

void Keyboard::setAttack(OIS::KeyCode key) {
    _attack = key;
}

OIS::KeyCode Keyboard::getUp() const {
    return _up;
}

OIS::KeyCode Keyboard::getDown() const {
    return _down;
}

OIS::KeyCode Keyboard::getLeft() const {
    return _left;
}

OIS::KeyCode Keyboard::getRight() const {
    return _right;
}

OIS::KeyCode Keyboard::getAttack() const {
    return _attack;
}

OIS::KeyCode Keyboard::getSave() const {
    return _save;
}

Keyboard::~Keyboard() {

}

void Keyboard::setAction(OIS::KeyCode key) {
    _action = key;
}

OIS::KeyCode Keyboard::getAction() const {
    return _action;
}
