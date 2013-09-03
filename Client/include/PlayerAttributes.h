#ifndef PLAYERATTRIBUTES_H_
#define PLAYERATTRIBUTES_H_

#include "SFML/Network.hpp"

struct PlayerAttributes {
  int hairID;
  int faceID;
  int bodyID;
};

inline sf::Packet& operator <<(sf::Packet& packet, const PlayerAttributes& player) {
  return packet << player.hairID << player.faceID << player.bodyID;
}

inline sf::Packet& operator >>(sf::Packet& packet, PlayerAttributes& player) {
  return packet >> player.hairID >> player.faceID >> player.bodyID;
}

#endif