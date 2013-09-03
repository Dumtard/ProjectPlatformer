#ifndef MAP_H_
#define MAP_H_

#include <vector>

class Map {
public:
  Map();
  ~Map();

  std::vector<int>& getMap();
  void setMap(std::vector<int> mapArray);

  void setWidth(int width);
  int getWidth();

  void setHeight(int height);
  int getHeight();

private:
  std::vector<int> mapArray_;

  int width_;
  int height_;
};

#endif