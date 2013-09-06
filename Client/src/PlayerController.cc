#include "PlayerController.h"

#include <iostream>

PlayerController::PlayerController(ObjectManager &objectManager, Map &map,
                                   sf::View &camera, Network &network) 
: camera_(camera), objectManager_(objectManager), map_(map), network_(network) {
}

PlayerController::~PlayerController() {

}

void PlayerController::setAccount(std::string name) {
  name_ = name;
}

void PlayerController::input() {
  Player *player = objectManager_.getPlayer(name_);

  //Can only move while window is in focus
  if (inFocus) {
    // Left and right at the same time will be idle
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) &&
      (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
      player->setVelocity(sf::Vector2f(0, player->getVelocity().y));
      if (player->grounded_) {
        player->changeAnimation("standing");
      }
    //Move right with walking animation
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      player->setIsFacingLeft(false);
      player->setVelocity(sf::Vector2f(4, player->getVelocity().y));
      if (player->grounded_) {
        player->changeAnimation("walking");
      }

    //Move left with walking animation
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      player->setIsFacingLeft(true);
      player->setVelocity(sf::Vector2f(-4, player->getVelocity().y));
      if (player->grounded_) {
        player->changeAnimation("walking");
      }

    //Right and Left not pressed idle animation
    } else if ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) &&
      (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
      player->setVelocity(sf::Vector2f(0, player->getVelocity().y));
      if (player->grounded_) {
        player->changeAnimation("standing");
      }
    }

    // Jumping
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      if (!player->isJumping() && player->grounded_) {
        player->setIsJumping(true);
        player->grounded_ = false;
        player->setVelocity(sf::Vector2f(player->getVelocity().x,
                                        player->getVelocity().y - 5));
        clock.restart();
        player->changeAnimation("jumping");

        network_.addJump(player->getVelocity(), objectManager_);
      }
    }
  }
}

void PlayerController::input(sf::Event event) {
  Player *player = objectManager_.getPlayer(name_);

  switch (event.type) {
    case sf::Event::LostFocus:
      inFocus = false;
      break;
    case sf::Event::GainedFocus:
      inFocus = true;
      break;
    case sf::Event::KeyPressed:
      if (event.key.code == sf::Keyboard::Right) {
        network_.addMove(player->getVelocity(), objectManager_);
      }
      if (event.key.code == sf::Keyboard::Left) {
        network_.addMove(player->getVelocity(), objectManager_);
      }
      break;
    case sf::Event::KeyReleased:
      if (event.key.code == sf::Keyboard::Right) {
        network_.addMove(player->getVelocity(), objectManager_);
      }
      if (event.key.code == sf::Keyboard::Left) {
        network_.addMove(player->getVelocity(), objectManager_);
      }
      break;
    default:
      break;
  }
}

void PlayerController::update() {
  for (auto it = objectManager_.getPlayers().begin();
       it != objectManager_.getPlayers().end(); ++it) {
    Player *player = it->second;

    // Jumping
    if (player->isJumping() && player->getVelocity().y <= -10) {
      player->setIsJumping(false);
      clock.restart();
    } else if (player->isJumping()) {
      player->changeAnimation("jumping");
      player->setVelocity(sf::Vector2f(player->getVelocity().x,
                                       player->getVelocity().y - 2));
    }

    // std::cout << it->first << player->getPosition().x << std::endl;

    //Apply gravity
    player->setVelocity(sf::Vector2f(player->getVelocity().x,
                                     player->getVelocity().y + 1));
    player->updateAnimation();
    player->move(player->getVelocity());

    // std::cout << it->first << player->getPosition().x << std::endl;

    //This was added to not allow jumping while falling
    //and changing the animation to a falling animation
    if (player->getVelocity().y > 3) {
      player->changeAnimation("jumping");
      player->grounded_ = false;
    }

    //Terminal velocity added to remove falling through the floor
    if (player->getVelocity().y > 24) {
      player->setVelocity(sf::Vector2f(player->getVelocity().x, 24));
    }

    //Collision detection with the top of the tiles
    for (auto it = map_.getTiles().begin(); it != map_.getTiles().end(); ++it) {
      if (it->getState() == 2 && player->getVelocity().y > 0) {
        if (player->getBoundingBox().intersects(it->getBoundingBox())) {
          player->setPosition(sf::Vector2f(player->getPosition().x, 
                                           it->getBoundingBox().top-64));
          player->setVelocity(sf::Vector2f(player->getVelocity().x, 0));
          player->grounded_ = true;

          if (player->getVelocity().x == 0) {
            player->changeAnimation("standing");
          } else {
            player->changeAnimation("walking");
          }
        }
      }
    }

    //Do not allow player to move outside of the map bounds
    if (player->getPosition().x < 19.5) {
      player->setPosition(sf::Vector2f(19.5, player->getPosition().y));
      player->setVelocity(sf::Vector2f(0, player->getVelocity().y));
    }

    if (player->getPosition().x > map_.getWidth() - 19.5) {
      player->setPosition(sf::Vector2f(map_.getWidth() - 19.5, player->getPosition().y));
      player->setVelocity(sf::Vector2f(0, player->getVelocity().y));
    }

    if (player->getPosition().y > map_.getHeight() - 64) {
      player->setPosition(sf::Vector2f(player->getPosition().x, map_.getHeight() - 64));
      player->setVelocity(sf::Vector2f(player->getVelocity().x, 0));
      player->grounded_ = true;
    }
  }

  Player *player = objectManager_.getPlayer(name_);

  //Center camera on player
  camera_.setCenter(player->getPosition());

  //Keep camera on the map
  if ((camera_.getCenter().x - (camera_.getSize().x / 2)) < 0) {
    camera_.setCenter((camera_.getSize().x / 2), camera_.getCenter().y);    
  } else if ((camera_.getCenter().x + (camera_.getSize().x / 2)) > map_.getWidth()) {
    camera_.setCenter(map_.getWidth() - (camera_.getSize().x / 2),
                      camera_.getCenter().y);    
  }
  if ((camera_.getCenter().y + (camera_.getSize().y / 2)) > map_.getHeight()) {
    camera_.setCenter(camera_.getCenter().x,
                      map_.getHeight() - (camera_.getSize().y / 2));    
  } else if ((camera_.getCenter().y - (camera_.getSize().y / 2)) < 0) {
    camera_.setCenter(camera_.getCenter().x, (camera_.getSize().y / 2));
  }
}