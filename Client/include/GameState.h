#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "SFML/Graphics.hpp"

#include "Network.h"

class GameState {
public:
  GameState(sf::RenderWindow &window, Network &network);
  virtual ~GameState();

  virtual void getNetwork();
  virtual void input(sf::Event event)=0;
  virtual void input()=0;
  virtual void update()=0;
  virtual void render(float delta)=0;
  virtual void setNetwork();

protected:
  sf::RenderWindow &window_;
  Network &network_;
};

#endif