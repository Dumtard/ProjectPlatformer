#ifndef MAP_H_
#define MAP_H_

#include <cstdlib>
#include <ctime>
#include <vector>

#include "SFML/Graphics.hpp"

#include "Sprite.h"
#include "Tile.h"

class Map {
public:
  Map();
  ~Map();

  void load(std::vector<int> mapArray);
  void generate();

  int getWidth();
  void setWidth(int width);

  int getHeight();
  void setHeight(int height);

  std::vector<Tile>& getTiles();

private:
  int width_;
  int height_;

  std::vector<Tile> tiles_;

  sf::Texture texture_;
  Sprite sprite_;

  void generateBase();
  void generatePlatforms();
};

#endif