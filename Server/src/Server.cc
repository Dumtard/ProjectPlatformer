#include "Server.h"

#include <iostream>

sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& vector) {
  return packet << vector.x << vector.y;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& vector) {
  return packet >> vector.x >> vector.y;
}

Server::Server() {
  clientPort = 1337;

  if (socket.bind(1338) != sf::Socket::Done) {
    std::cout << "Error binding socket to port";
  }
  socket.setBlocking(false);

  std::cout << "Server running" << std::endl;
}

Server::~Server() {

}

void Server::running() {
  while(true) {
    packet.clear();
    receive();
    send();
  }
}

void Server::receive() {
  sf::IpAddress client;
  unsigned short port;

  socket.receive(packet, client, port);

  if (packet.getDataSize() > 0) {
    packet >> buffer;
  }

  if (buffer.compare("CON") == 0) {
    bool connection;

    packet >> buffer >> connection;

    if (connection) {
      //Connected
      //Add buffer (account), clientIP to map of current users
      std::cout << buffer << " has connected" << std::endl;

      clients_.insert(std::pair<sf::IpAddress, Player>(client, (Player())));
      clients_.at(client).setPlayerName(buffer);

      for (auto it = clients_.begin(); it != clients_.end(); ++it) {
        (it->second).getPacket() << "CON" << (it->second).getPlayerName();
        (it->second).getPacket() << connection;
      }

      std::cout << "Clients: " << clients_.size() << std::endl;
    } else {
      //Disconnect
      //Remove buffer (account) from map of current users
      std::cout << clients_.at(client).getPlayerName()
                << " has disconnected" << std::endl;

      clients_.erase(client);

      for (auto it = maps_.begin(); it != maps_.end(); ++it) {
        if (clients_.size() == 0) {
          maps_.erase(it);
          break;
        }
      }

      std::cout << "Clients: " << clients_.size() << std::endl;
    }
  } else if (buffer.compare("MAP") == 0) {
    bool request;
    packet >> request;
    if (request) {
      packet.clear();
      if (clients_.size() < 1) {
        packet << "MAP" << false;
        socket.send(packet, client, clientPort);
        packet.clear();
      } else {
        packet << "MAP" << true;

        packet << maps_[0].getWidth() << maps_[0].getHeight();

        for (auto x : maps_[0].getMap()) {
          packet << x;
        }
        socket.send(packet, client, clientPort);
        packet.clear();
      }
    } else {
      maps_.push_back((Map()));
      int width, height, x;
      packet >> width >> height;
      maps_[0].setWidth(width);
      maps_[0].setHeight(height);
      while (packet >> x) {
        maps_[0].getMap().push_back(x);
      }
      packet.clear();
    }
    buffer = "";
  } else if (buffer.compare("MOV") == 0) {
    sf::Vector2f velocity;
    sf::Vector2f position;
    packet >> velocity;
    // std::cout << buffer << ": " << velocity.x << "," << velocity.y << std::endl;
    clients_.at(client).setVelocity(velocity);
    clients_.at(client).getPacket() << "MOV";
    clients_.at(client).getPacket() << clients_.at(client).getPlayerName();
    clients_.at(client).getPacket() << clients_.at(client).getVelocity();
    packet >> buffer >> position;
    // std::cout << buffer << ": " << position.x << ", " << position.y << std::endl;
    clients_.at(client).setPosition(position);
    clients_.at(client).getPacket() << "POS" << clients_.at(client).getPosition();
  } else if (buffer.compare("JMP") == 0) {
    sf::Vector2f velocity;
    sf::Vector2f position;

    packet >> velocity;
  // std::cout << buffer << ": " << velocity.x << "," << velocity.y << std::endl;
    clients_.at(client).setVelocity(velocity);
    clients_.at(client).getPacket() << "JMP";
    clients_.at(client).getPacket() << clients_.at(client).getPlayerName();
    clients_.at(client).getPacket() << clients_.at(client).getVelocity();
    packet >> buffer >> position;
    // std::cout << buffer << ": " << position.x << ", " << position.y << std::endl;
    clients_.at(client).setPosition(position);
    clients_.at(client).getPacket() << "POS" << clients_.at(client).getPosition();
  }
  packet.clear();
}

void Server::send() {
  for (auto it = clients_.begin(); it != clients_.end(); ++it) {
    if ((it->second).hasPacket()) {
      // std::cout << it->first << ": has packet" << std::endl;
      for (auto itr = clients_.begin(); itr != clients_.end(); ++itr) {
        if (it->first != itr->first) {
          // std::cout << it->first << ": sending to " << itr->first << std::endl;
          socket.send((it->second).getPacket(), itr->first, clientPort);
        }
      }
      (it->second).getPacket().clear();
    }
  }
}

// CharacterAttributes getAttributes(std::string name) {
//   CharacterAttributes character;
//   try {
//     mysqlpp::Connection conn(false);
//     conn.connect("platformer", "localhost", "root", "admin");

//     mysqlpp::Query query = conn.query();


//     query << "SELECT `hairID`,`faceID`,`bodyID` " <<
//              "FROM `Attributes` " <<
//              "WHERE `CharacterID` = (SELECT `id` " <<
//                                     "FROM `Characters` " <<
//                                     "WHERE `Name` = '" + name + "');";

//     mysqlpp::StoreQueryResult ares = query.store();

//     for (size_t i = 0; i < ares.num_rows(); i++) {
//       character.hairID = ares[i]["hairID"];
//       character.faceID = ares[i]["faceID"];
//       character.bodyID = ares[i]["bodyID"];
//     }

//   } catch (mysqlpp::BadQuery er) {
//     std::cerr << "Error: " << er.what() << std::endl;
//   } catch (const mysqlpp::BadConversion& er) {
//     std::cerr << "Error: " << er.what() << std::endl;
//   } catch (const mysqlpp::Exception& er) {
//     std::cerr << "Error: " << er.what() << std::endl;
//   }
//   return character;
// }







// struct CharacterAttributes {
//   int hairID;
//   int faceID;
//   int bodyID;
// };

// struct CharacterEquipment {
//   // Later
// };

// struct PlayerPacket {
//   int id_;
//   std::string name_;
//   sf::Vector2f position_;

//   //Animation?

//   CharacterAttributes attributes_;
//   //CharacterEquipment equipment_;

//   bool pos, eqp, atb, ani;
// };


// sf::Packet& operator <<(sf::Packet& packet,
// const CharacterAttributes& character) {
//   return packet << character.hairID << character.faceID << character.bodyID;
// }

// sf::Packet& operator >>(sf::Packet& packet, CharacterAttributes& character) {
//   return packet >> character.hairID >> character.faceID >> character.bodyID;
// }