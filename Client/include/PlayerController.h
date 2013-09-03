#ifndef PLAYERCONTROLLER_H_
#define PLAYERCONTROLLER_H_

#include "SFML/Graphics.hpp"

#include "Controller.h"
#include "Map.h"
#include "Network.h"
#include "ObjectManager.h"

class PlayerController : public Controller{
public:
  PlayerController(ObjectManager &objectManager, Map &map, sf::View &camera,
                   Network &network);
  ~PlayerController();

  void setAccount(std::string name);

  void input(sf::Event);
  void input();
  void update();

private:
  sf::View &camera_;

  ObjectManager &objectManager_;
  Map &map_;
  Network &network_;

  sf::Clock clock;

  bool inFocus = true;

  std::string name_;
};

#endif