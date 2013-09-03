#ifndef VECTOR2F_H_
#define VECTOR2F_H_

#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"

inline sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& vector) {
  return packet << vector.x << vector.y;
}

inline sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& vector) {
  return packet >> vector.x >> vector.y;
}

#endif