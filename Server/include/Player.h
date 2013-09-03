#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"

class Player {
public:
  Player();
  ~Player();

  bool hasPacket();
  sf::Packet& getPacket();

  sf::Vector2f getPosition();
  void setPosition(sf::Vector2f position);

  sf::Vector2f getVelocity();
  void setVelocity(sf::Vector2f velocity);

  std::string getPlayerName();
  void setPlayerName(std::string name);

private:
  std::string playerName_;

  sf::Vector2f position_;
  sf::Vector2f velocity_;

  sf::Packet packet_;
};

#endif
