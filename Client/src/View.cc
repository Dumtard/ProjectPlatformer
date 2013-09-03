#include "View.h"

#include <iostream>

View::View(sf::RenderWindow &window) : window_(window) {

}

View::~View() {

}

void View::loadTextures(std::string folder, int file) {
  sf::Texture texture;

  std::stringstream sstream;
  sstream << "resources/images/" << folder << "/" << file << ".png";

  texture.loadFromFile(sstream.str());
  texture.setSmooth(false);

  texture_.insert(std::pair<int, sf::Texture>(file, texture));
}

void View::render(float delta) {
}