#ifndef SERVER_H_
#define SERVER_H_

#include <map>
#include <vector>

#include "mysql++.h"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"

#include "Map.h"
#include "Player.h"

class Server {
public:
  Server();
  ~Server();

  void running();

private:
  sf::UdpSocket socket;
  sf::Packet packet;

  unsigned short clientPort;

  std::string buffer;

  std::map<sf::IpAddress, Player> clients_;

  std::vector<Map> maps_;

  void receive();
  void send();
};

#endif