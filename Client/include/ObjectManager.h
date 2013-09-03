#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include <map>
#include <string>
#include <vector>

#include "Entity.h"
#include "Player.h"

class ObjectManager {
public:
  ObjectManager();
  ~ObjectManager();

  void add(Entity entity);
  void add(std::string name, Player *player);

  std::map<std::string, Player*>& getPlayers();
  int getNumberOfEntities();

  Entity getEntity(int index);
  Player* getPlayer(std::string name);

private:
  std::vector<Entity> entities_;
  std::map<std::string, Player*> players_;
};

#endif