#ifndef PLAYER_H_
#define PLAYER_H_

#include <array>
#include <string>
#include <map>

#include "SFML/Graphics.hpp"

#include "Animation.h"
#include "PlayerAttributes.h"
#include "Sprite.h"

struct PlayerEquipment {
  int amuletID;
  std::array<int, 2> ringIDs;
  int helmetID;
  int shouldersID;
  int chestID;
  int pantsID;
  int beltID;
  int glovesID;
  int bootsID;
};

class Player {
public:
  Player();
  ~Player();

  Sprite getSprite();

  sf::Vector2f getPosition();
  void setPosition(sf::Vector2f position);
  void move(sf::Vector2f offset);

  sf::Vector2f getVelocity();
  void setVelocity(sf::Vector2f velocity);

  sf::FloatRect getBoundingBox();
  void setBoundingBox(sf::FloatRect boundingBox);

  bool isFacingLeft();
  void setIsFacingLeft(bool isFacingLeft);

  bool isJumping();
  void setIsJumping(bool isJumping);

  void setOrigin(sf::Vector2f origin);

  void load(std::string name);

  void addAnimation(std::string name, sf::Texture &texture,
                    int row, int frames, int fps);
  void changeAnimation(std::string name);
  void updateAnimation();

public:

  Animation *currentAnimation_;
  std::map<std::string, Animation*> animations_;

  sf::Vector2f velocity_;
  sf::Vector2f position_;

  bool isFacingLeft_;
  bool isJumping_ = false;

  sf::FloatRect boundingBox_;

  sf::Texture texturetemp;
  Sprite body;

public:
  bool grounded_ = true;

  PlayerAttributes attributes_;
  PlayerEquipment equipment_;
};

#endif