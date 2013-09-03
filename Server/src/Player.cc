#include "Player.h"

#include <iostream>

Player::Player() {

}

Player::~Player() {

}

sf::Vector2f Player::getPosition() {
  return position_;
}

void Player::setPosition(sf::Vector2f position) {
  position_ = position;
}

sf::Vector2f Player::getVelocity() {
  return velocity_;
}

void Player::setVelocity(sf::Vector2f velocity) {
  velocity_ = velocity;
}

std::string Player::getPlayerName() {
  return playerName_;
}

void Player::setPlayerName(std::string name) {
  playerName_ = name;
}

bool Player::hasPacket() {
  if (packet_.getDataSize() > 0) {
    return true;
  } else {
    return false;
  }
}

sf::Packet& Player::getPacket() {
  return packet_;
}