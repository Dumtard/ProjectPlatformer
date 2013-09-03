#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "SFML/Graphics.hpp"

class GameState {
public:
  GameState();
  virtual ~GameState();

  virtual void getNetwork()=0;
  virtual void input(sf::Event event)=0;
  virtual void input()=0;
  virtual void update()=0;
  virtual void render(float delta)=0;
  virtual void setNetwork()=0;
};

#endif