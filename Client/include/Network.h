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
  Network(ObjectManager &objectManager, MainView &view);
  ~Network();

  void connect(std::string account);
  void disconnect();

  void receive(ObjectManager &objectManager);
  void send();

  void addMove(sf::Vector2f velocity);
  void addJump(sf::Vector2f velocity);

  void setMap(Map &map);
  bool getMap(Map &map);

private:
  ObjectManager &objectManager_;
  MainView &view_;

  sf::UdpSocket socket;
  sf::Packet packet;

  sf::IpAddress server;
  unsigned short sPort;

  std::string buffer;

  std::string account_;
  std::string character_;
};

#endif