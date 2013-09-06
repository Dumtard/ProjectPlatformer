#ifndef LOGINSTATE_H_
#define LOGINSTATE_H_

#include <memory>

#include "SFML/Graphics.hpp"

#include "Application.h"
#include "GameState.h"
#include "Network.h"

class LoginState : public GameState {
public:
  LoginState(sf::RenderWindow &window, Network &network);
  ~LoginState();
  
  void input();
  void input(sf::Event event);
  void update();
  void render(float delta);

private:
  sf::Font font_;
  sf::Text text_;

  std::string account_;
};

#endif