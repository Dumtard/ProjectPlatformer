#include "Network.h"

#include <iostream>

Network::Network() {
  server = sf::IpAddress(192, 168, 2, 22);
  // server = sf::IpAddress("dumtard.no-ip.biz");
  sPort = 1338;

  if (socket.bind(1337) != sf::Socket::Done) {
    std::cout << "Error binding to port";
  }

  socket.setBlocking(false);
}

Network::~Network() {

}

void Network::connect(std::string account) {
  account_ = account;

  packet.clear();
  packet << "CON" << account_ << true;
  socket.send(packet, server, sPort);
  packet.clear();
}

void Network::disconnect() {
  if (account_.compare("") == 0) {
    return;
  }
  
  packet.clear();
  packet << "CON" << account_ << false;
  socket.send(packet, server, sPort);
  packet.clear();
}

void Network::addMove(sf::Vector2f velocity, ObjectManager &objectManager) {
  packet << "MOV" << velocity;
  packet << "POS" << objectManager.getPlayer(account_)->getPosition();
}

void Network::addJump(sf::Vector2f velocity, ObjectManager &objectManager) {
  packet << "JMP" << velocity;
  packet << "POS" << objectManager.getPlayer(account_)->getPosition();
}

void Network::setMap(Map &map) {
  packet.clear();
  packet << "MAP" << false;
  packet << map.getWidth()/90 << map.getHeight()/60;
  for (auto x : map.getTiles()) {
    packet << x.getState();
  }
  socket.send(packet, server, sPort);
  packet.clear();
}

bool Network::getMap(Map &map) {
  sf::IpAddress temp;
  unsigned short temp2;
  socket.setBlocking(true);
  packet.clear();
  packet << "MAP" << true;
  socket.send(packet, server, sPort);
  packet.clear();
  socket.receive(packet, temp, temp2);
  socket.setBlocking(false);
  
  packet >> buffer;

  if (buffer.compare("MAP") == 0) {
    bool isMap;
    packet >> isMap;

    if (!isMap) {
      return isMap;
    }

    int width, height, x;
    std::vector<int> mapArray;

    packet >> width >> height;
    while (packet >> x) {
      mapArray.push_back(x);
    }
    map.setHeight(height);
    map.setWidth(width);
    map.load(mapArray);

    packet.clear();
    return isMap;
  }
  packet.clear();
  return false;
}

void Network::receive(ObjectManager &objectManager, View &view) {
  sf::IpAddress temp;
  unsigned short temp2;
  packet.clear();
  socket.receive(packet, temp, temp2);

  packet >> buffer;

  if (buffer.compare("CON") == 0) {
    bool connection;
    packet >> buffer >> connection;
    if (connection) {
      Player *player = new Player();
      objectManager.add(buffer, player);
      view.set(buffer);
    } else {
      //Remove player from objectManager
    }
  } else if (buffer.compare("MOV") == 0) {
    packet >> buffer;
    Player *player = objectManager.getPlayer(buffer);
    sf::Vector2f velocity;
    sf::Vector2f position;
    packet >> velocity;
    packet >> buffer >> position;
    player->setVelocity(velocity);
    player->setPosition(position);
    if (velocity.x != 0) {
      player->changeAnimation("walking");
    } else {
      player->changeAnimation("standing");
    }
    if (velocity.x > 0) {
      player->setIsFacingLeft(false);
    } else if (velocity.x < 0) {
      player->setIsFacingLeft(true);
    }
  } else if (buffer.compare("JMP") == 0) {
    packet >> buffer;
    Player *player = objectManager.getPlayer(buffer);
    sf::Vector2f velocity;
    sf::Vector2f position;
    packet >> velocity;
    packet >> buffer >> position;
    player->setVelocity(velocity);
    player->setPosition(position);
    player->setIsJumping(true);
    player->changeAnimation("jumping");
  }

  packet.clear();
}

void Network::send() {
  socket.send(packet, server, sPort);
  packet.clear();
}