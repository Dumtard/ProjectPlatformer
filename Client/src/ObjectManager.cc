#include "ObjectManager.h"

#include <iostream>

ObjectManager::ObjectManager() {

}

ObjectManager::~ObjectManager() {

}

void ObjectManager::add(Entity entity) {
  entities_.push_back(entity);
}

void ObjectManager::add(std::string name, Player *player) {
  players_.insert(std::pair<std::string, Player*>(name, player));
}

std::map<std::string, Player*>& ObjectManager::getPlayers() {
  return players_;
}

int ObjectManager::getNumberOfEntities() {
  return entities_.size();
}

Entity ObjectManager::getEntity(int index) {
  return entities_[index];
}

Player* ObjectManager::getPlayer(std::string name) {
  return players_.at(name);
}