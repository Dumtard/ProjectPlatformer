#include "Sprite.h"

Sprite::Sprite() : sf::Sprite() {
}

Sprite::Sprite(const sf::Texture &texture) : sf::Sprite(texture) {
}

Sprite::Sprite(const sf::Texture &texture, const sf::IntRect &rectangle)
      : sf::Sprite(texture, rectangle) {
}

sf::Vector2f Sprite::getOffset() {
  return offset_;
}

void Sprite::setOffset(sf::Vector2f offset) {
  offset_ = offset;
}