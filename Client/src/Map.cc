#include "Map.h"

#include <iostream>

Map::Map() {
  texture_.loadFromFile("resources/maps/tiles/0.png");
}

Map::~Map() {

}

std::vector<Tile>& Map::getTiles() {
  return tiles_;
}

int Map::getHeight() {
  return height_ * 60;
}

void Map::setHeight(int height) {
  height_ = height;
}

int Map::getWidth() {
  return width_ * 90;
}

void Map::setWidth(int width) {
  width_ = width;
}

void Map::load(std::vector<int> mapArray) {
  tiles_.reserve(mapArray.size());
  
  for (unsigned int i = 0; i < mapArray.size(); i++) {
    Tile tile;
    tile.setPosition(sf::Vector2f((i % width_) * 90, (i / width_) * 60));
    tile.setState(mapArray[i]);
    tiles_.push_back(tile);
  }
  
  generate();
}

void Map::generate() {
  if (tiles_.size() == 0) {
    srand(time(0));
    width_ = rand() % 90 + 10;
    height_ = rand() % 90 + 10;
    tiles_.reserve(width_ * height_);

    for (int i = 0; i < width_ * height_; i++) {
      Tile tile;
      tile.setPosition(sf::Vector2f((i % width_) * 90, (i / width_) * 60));
      tile.setState(0);
      tiles_.push_back(tile);
    }

    generateBase();
    generatePlatforms();
  }

  for (auto it = tiles_.begin(); it != tiles_.end() - width_; ++it) {
    if ((it+width_)->getState() == 1 && it->getState() != 1) {
      it->setState(2);
      it->setSprite(texture_, 0, rand() % 2);
    } else if (it->getState() == 1) {
      it->setSprite(texture_, 1, rand() % 5);
    }
  }

  for (auto it = tiles_.end() - width_; it != tiles_.end(); ++it) {
    if (it->getState() == 1) {
      it->setSprite(texture_, 1, rand() % 5);
    }
  }
}

void Map::generateBase() {
  //Bottom can be up to 5 layers high
  for (int i = 0; i < 5; i++) {
    //Go across each layer from right to left
    for (auto it = tiles_.end() - (i * width_);
         it != tiles_.end() - ((i + 1) * width_); --it) {
      int random = rand() % 100;
      //Each layer has 20 percent less chance of making a block
      if (random >= i * 20) {
        //First layer must have solid blocks
        if (i == 0) {
          (it-1)->setState(1);
          (it-1)->setSprite(texture_, 1, rand() % 5);
          continue;

        //Not first layer
        } else {
          //If the second last was a block and the last was not a block
          //skip this block so that there is not 1 empty block spaces
          if ((it+1)->getState() == 1 && (it)->getState() != 1) {
            continue;
          }
          //Block can only be placed if it is in the middle of atleast
          //3 blocks on the layer below it
          //Right end block only needs 2 under it
          if ((it - tiles_.begin()) % width_ == 0) {
            if (((it-1)+width_)->getState() == 1 &&
                ((it-1)+width_-1)->getState() == 1) {
              (it-1)->setState(1);
              (it-1)->setSprite(texture_, 1, rand() % 5);
              continue;
            }
          //Left end block only needs 2 under it
          } else if ((it - tiles_.begin()) % width_ == 1) {
            if (((it-1)+width_)->getState() == 1 &&
                ((it-1)+width_+1)->getState() == 1) {
              (it-1)->setState(1);
              (it-1)->setSprite(texture_, 1, rand() % 5);
              continue;
            }
          //Middle block needs 3 under it
          } else {
            if (((it-1)+width_)->getState() == 1 &&
                ((it-1)+width_-1)->getState() == 1 &&
                ((it-1)+width_+1)->getState() == 1) {
              (it-1)->setState(1);
              (it-1)->setSprite(texture_, 1, rand() % 5);
              continue;
            }
          }
        }
      }
    }
  }
}

void Map::generatePlatforms() {
  for (int i = 2; i < height_ - 1; ++i) {
    for (auto it = tiles_.end() - (i * width_);
         it != tiles_.end() - ((i + 1) * width_); --it) {
      int random = rand() % 100;
      if (random < 5) {
        if (((it-2)+width_)->getState() != 1 &&
             ((it-2)+(width_ * 2))->getState() != 1) {
          (it-2)->setState(1);
          (it-2)->setSprite(texture_, 1, rand() % 5);
        }
        if (((it-1)+width_)->getState() != 1 &&
             ((it-1)+(width_ * 2))->getState() != 1) {
          (it-1)->setState(1);
          (it-1)->setSprite(texture_, 1, rand() % 5);
        }
        if (((it)+width_)->getState() != 1 &&
             ((it)+(width_ * 2))->getState() != 1) {
          (it)->setState(1);
          (it)->setSprite(texture_, 1, rand() % 5);
        }
        //extend platforms
      }
    }
  }
}