#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <iostream>
#include <memory>

#include "SFML/Graphics.hpp"

#include "LoginState.h"
#include "MainState.h"
#include "Player.h"

class Application {
public:
  static Application& getInstance() {
    static Application instance;
    return instance;
  }
  ~Application();

  void loop();

  //Others
  void changeState(std::unique_ptr<GameState> state);

private:
  Application() {
    initialize();
  };

  Application(Application const&);
  void operator=(Application const&);

  void initialize();

  sf::RenderWindow window_;
  sf::Image icon_;
  sf::Event event_;

  std::unique_ptr<GameState> state_;

  Network network_;

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
};

#endif