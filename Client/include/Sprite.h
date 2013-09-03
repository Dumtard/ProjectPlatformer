#ifndef SPRITE_H_
#define SPRITE_H_

#include "SFML/Graphics.hpp"


class Sprite : public sf::Sprite {
public:
  Sprite();
  Sprite(const sf::Texture &texture);
  Sprite(const sf::Texture &texture, const sf::IntRect &rectangle);

  sf::Vector2f getOffset();
  void setOffset(sf::Vector2f offset);

private:
  sf::Vector2f offset_;
};

#endif