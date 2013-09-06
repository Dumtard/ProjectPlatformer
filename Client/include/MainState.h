#ifndef MAINSTATE_H_
#define MAINSTATE_H_

#include <memory>

#include "GameState.h"
#include "MainView.h"
#include "Map.h"
#include "Network.h"
#include "ObjectManager.h"
#include "Player.h"
#include "PlayerController.h"

class MainState : public GameState {
public:
  MainState(sf::RenderWindow &window, Network &network, std::string name);
  ~MainState();

  void getNetwork();
  void input(sf::Event event);
  void input();
  void update();
  void render(float delta);
  void setNetwork();
  
private:
  sf::View camera_;

  MainView view_;
  PlayerController controller_;

  ObjectManager objectManager_;

  Map currentMap_;

  std::string name_;
};

#endif