#include "Player.h"

#include <iostream>

Player::Player() {
  attributes_.hairID = 0;
  attributes_.faceID = 0;
  attributes_.bodyID = 0;

  equipment_.amuletID = 0;
  equipment_.ringIDs[0] = 0;
  equipment_.ringIDs[1] = 0;
  equipment_.helmetID = 0;
  equipment_.shouldersID = 0;
  equipment_.chestID = 0;
  equipment_.pantsID = 0;
  equipment_.beltID = 0;
  equipment_.glovesID = 0;
  equipment_.bootsID = 0;

  position_ = sf::Vector2f(0, 0);
  velocity_ = sf::Vector2f(0, 0);
  boundingBox_ = sf::FloatRect(0, 0, 39, 8);
}

Player::~Player() {

}


void Player::setVelocity(sf::Vector2f velocity) {
  velocity_ = velocity;
}

sf::Vector2f Player::getVelocity() {
  return velocity_;
}

sf::FloatRect Player::getBoundingBox() {
  return boundingBox_;
}

void Player::setBoundingBox(sf::FloatRect boundingBox) {
  boundingBox_ = boundingBox;
}

Sprite Player::getSprite() {
  return currentAnimation_->getSprite();
  // return body;
}

sf::Vector2f Player::getPosition() {
  return position_;
}

void Player::setPosition(sf::Vector2f position) {
  position_ = position;
  boundingBox_ = sf::FloatRect(position_.x - 19.5f, position_.y + 56, 39, 8);
}

void Player::move(sf::Vector2f offset) {
  position_ = position_ + offset;
  boundingBox_ = sf::FloatRect(position_.x - 19.5f, position_.y + 56, 39, 8);
}

void Player::setIsFacingLeft(bool isFacingLeft) {
  isFacingLeft_ = isFacingLeft;
}

bool Player::isFacingLeft() {
  return isFacingLeft_;
}

void Player::setIsJumping(bool isJumping) {
  isJumping_ = isJumping;
}

bool Player::isJumping() {
  return isJumping_;
}

void Player::load(std::string name) {
  //Request info from server with name

  attributes_.bodyID=0;
  attributes_.hairID=1;
  attributes_.faceID=0;
}

void Player::addAnimation(std::string name, sf::Texture &texture, int row,
                          int frames, int fps) {
  Animation *animation = new Animation();
  animation->create(texture, row, frames, fps);
  animations_.insert(std::pair<std::string, Animation*>(name, animation));
}

void Player::changeAnimation(std::string name) {
  // std::cout << name << std::endl;
  if (currentAnimation_ != animations_[name]) {
    if (animations_.count(name) == 1) {
      currentAnimation_ = animations_[name];
    }
  }
}

void Player::updateAnimation() {
  currentAnimation_->update();
}