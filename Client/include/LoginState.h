#ifndef LOGINSTATE_H_
#define LOGINSTATE_H_

#include "GameState.h"

class LoginState : public GameState
{
public:
  LoginState();
  ~LoginState();
  
  void input(sf::Event event);
  void update();
  void render(float delta);

private:
};

#endif