#include "Entity.h"

Entity::Entity() {

}

Entity::~Entity() {

}

sf::Sprite Entity::getSprite() {
  return sprite_;
}

void Entity::setSprite(sf::Texture &texture) {
  sprite_.setTexture(texture);
}

void Entity::setPosition(sf::Vector2f position) {
  sprite_.setPosition(position);
}

void Entity::update() {

}