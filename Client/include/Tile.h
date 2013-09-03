#ifndef TILE_H_
#define TILE_H_

#include "SFML/Graphics.hpp"

#include "Sprite.h"

class Tile {
public:
  Tile();
  ~Tile();

  Sprite getSprite();
  void setSprite(sf::Texture &texture, int row, int tile);

  sf::Vector2f getPosition();
  void setPosition(sf::Vector2f position);

  int getState();
  void setState(int state);

  sf::FloatRect getBoundingBox();
  void setBoundingBox(sf::FloatRect boundingBox);

private:
  Sprite sprite_;

  sf::Vector2f position_;

  int state_;

  sf::FloatRect boundingBox_;
};

#endif