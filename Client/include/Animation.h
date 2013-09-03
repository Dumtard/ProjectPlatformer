#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "SFML/Graphics.hpp"
#include "Sprite.h"

class Animation {
public:
  Animation();
  ~Animation();

  void create(const sf::Texture &texture, int row, int frames, int fps);

  void start();
  void stop();

  void update();

  Sprite getSprite();

private:
  // void run();

  Sprite *currentSprite_;
  std::vector<Sprite> sprites_;

  sf::Clock clock;

  int numberOfFrames_;
  int currentFrame_;
  int framesPerSecond_;

};

#endif