#include "MainState.h"

#include <iostream>

MainState::MainState(sf::RenderWindow &window)
: window_(window), view_(window, objectManager_, currentMap_),
  controller_(objectManager_, currentMap_, camera_, network_),
  network_(objectManager_, view_) {
  
  camera_.reset(sf::FloatRect(0, 0, 800, 600));

  window.setView(camera_);

  std::cin >> name_;
  controller_.setAccount(name_);

  Player *player = new Player();
  objectManager_.add(name_, player);

  //Get Map from server or load and send
  if (!network_.getMap(currentMap_)) {
    currentMap_.generate();
    network_.setMap(currentMap_);
  }
  
  network_.connect(name_);

  //Get yourself
  // network_.getPlayerAttributes("Admin", player);

  //Get everyone else on the map

  view_.set(name_);
}

MainState::~MainState() {

}
void MainState::getNetwork() {
  network_.receive(objectManager_);
}

void MainState::input(sf::Event event) {
  controller_.input(event);
  
  if (event.type == sf::Event::Closed) {
    network_.disconnect();
  } else if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Escape) {
      network_.disconnect();
    }
  }
}

void MainState::input() {
  controller_.input();
}

void MainState::update() {
  controller_.update();
  window_.setView(camera_);
}

void MainState::render(float delta) {
  view_.render(delta);
}

void MainState::setNetwork() {
  network_.send();
}