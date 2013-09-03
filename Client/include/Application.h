#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <iostream>
#include <memory>

#include "SFML/Graphics.hpp"

#include "MainState.h"
#include "Player.h"

class Application
{
public:
  Application();
  ~Application();

  void loop();

private:
  sf::RenderWindow window;
  sf::Image icon;
  sf::Event event;

  std::unique_ptr<GameState> state_;

  //loop control
  sf::Clock clock;
  float elapsed;
  float lag;

  int framerate;
  float MS_PER_UPDATE;

  //loop functions
  void getNetwork();
  void input();
  void update();
  void render(float delta);
  void setNetwork();

  //Others
  void changeState(std::unique_ptr<GameState> state);
};

#endif