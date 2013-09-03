#ifndef ENTITY_H_
#define ENTITY_H_

#include "SFML/Graphics.hpp"

class Entity {
public:
  Entity();
  ~Entity();

  sf::Sprite getSprite();
  void setSprite(sf::Texture &texture);
  sf::Vector2f getPosition();

  void setPosition(sf::Vector2f position);

  void update();

private:
  sf::Sprite sprite_;
};

#endif