#ifndef NETWORK_H_
#define NETWORK_H_

#include <string>

#include "SFML/Network.hpp"

#include "MainView.h"
#include "Map.h"
#include "ObjectManager.h"
#include "Player.h"
#include "PlayerAttributes.h"
#include "Tile.h"
#include "Vector2f.h"

class Network {
public:
  Network();
  ~Network();

  void connect(std::string account);
  void disconnect();

  void receive(ObjectManager &objectManager, View &view);
  void send();

  void addMove(sf::Vector2f velocity, ObjectManager &objectManager);
  void addJump(sf::Vector2f velocity, ObjectManager &objectManager);

  void setMap(Map &map);
  bool getMap(Map &map);

private:
  sf::UdpSocket socket;
  sf::Packet packet;

  sf::IpAddress server;
  unsigned short sPort;

  std::string buffer;

  std::string account_;
  std::string character_;
};

#endif