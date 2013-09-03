#include "Tile.h"

#include <iostream>

Tile::Tile() {
 state_ = 0;
 // boundingBox_ = sf::FloatRect(0, 0, 90, 26);
}

Tile::~Tile() {

}

Sprite Tile::getSprite() {
  return sprite_;
}

void Tile::setSprite(sf::Texture &texture, int row, int tile) {
  sprite_.setTexture(texture);
  sprite_.setTextureRect(sf::IntRect(tile * 90, row * 60, 90, 60));

  if (state_ == 2) {
    boundingBox_ = sf::FloatRect(position_.x, position_.y + 34, 90, 24);
  }
}

sf::FloatRect Tile::getBoundingBox() {
  return boundingBox_;
}

void Tile::setBoundingBox(sf::FloatRect boundingBox) {
  boundingBox_ = boundingBox;
}

sf::Vector2f Tile::getPosition() {
  return position_;
}

void Tile::setPosition(sf::Vector2f position) {
  position_ = position;
}

int Tile::getState() {
  return state_;
}

void Tile::setState(int state) {
  state_ = state;
}