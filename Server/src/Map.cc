#include "Map.h"

Map::Map() {

}

Map::~Map() {

}

std::vector<int>& Map::getMap() {
  return mapArray_;
}

void Map::setMap(std::vector<int> mapArray) {
  mapArray_ = mapArray;
}

void Map::setWidth(int width) {
  width_ = width;
}

int Map::getWidth() {
  return width_;
}

void Map::setHeight(int height) {
  height_ = height;
}

int Map::getHeight() {
  return height_;
}