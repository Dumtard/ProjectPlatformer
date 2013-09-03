#ifndef VIEW_H_
#define VIEW_H_

#include <map>
#include <sstream>
#include <string>

#include "SFML/Graphics.hpp"

class View {
public:
  View(sf::RenderWindow &window);
  ~View();

  void loadTextures(std::string folder, int file);

  void render(float delta);

  virtual void set(std::string name)=0;

protected:
  sf::RenderWindow &window_;
  std::map<int, sf::Texture> texture_;
};

#endif