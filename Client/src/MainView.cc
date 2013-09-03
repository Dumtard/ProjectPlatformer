#include "MainView.h"

#include <iostream>

MainView::MainView(sf::RenderWindow &window,
                   ObjectManager &objectManager,
                   Map &map)
  : View(window), objectManager_(objectManager), map_(map) {

}

MainView::~MainView() {

}

void MainView::set(std::string name) {
  Player *player = objectManager_.getPlayers().at(name);

  if (texture_.count(player->attributes_.bodyID) == 0) {
    loadTextures("body", player->attributes_.bodyID);
    player->addAnimation("walking", texture_.at(player->attributes_.bodyID),
                        1, 4, 5);
    player->addAnimation("jumping", texture_.at(player->attributes_.bodyID),
                        2, 1, 1);
    player->addAnimation("standing", texture_.at(player->attributes_.bodyID),
                        0, 4, 2);

    player->changeAnimation("standing");
    player->setPosition(sf::Vector2f(100, 100));
  } else {
    player->addAnimation("walking", texture_.at(player->attributes_.bodyID),
                        1, 4, 5);
    player->addAnimation("jumping", texture_.at(player->attributes_.bodyID),
                        2, 1, 1);
    player->addAnimation("standing", texture_.at(player->attributes_.bodyID),
                        0, 4, 2);
    player->changeAnimation("standing");
  }
}

void MainView::render(float delta) {
  renderMap(delta);
  renderPlayer(delta);
}

void MainView::renderPlayer(float delta) {
  for (auto it = objectManager_.getPlayers().begin();
       it != objectManager_.getPlayers().end(); ++it) {
    Player *player = it->second;

    Sprite body = player->getSprite();

    body.setOrigin(32, 0);

    if (!player->isFacingLeft()) {
      body.scale(-1.0f, 1.0f);
    }

    body.setPosition(player->getPosition());
    body.move(player->getVelocity() * delta);

    //Check sprite collision??

    window_.draw(body);
  }
}

void MainView::renderMap(float delta) {
  for (auto it = map_.getTiles().begin(); it != map_.getTiles().end(); ++it) {
    Sprite tile = it->getSprite();
    tile.setPosition(it->getPosition());
    window_.draw(tile);
  }
}