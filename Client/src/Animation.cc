#include "Animation.h"

#include <iostream>

Animation::Animation() {
  framesPerSecond_ = 0;
  currentFrame_ = 0;
  numberOfFrames_ = 0;
}

Animation::~Animation() {

}

void Animation::create(const sf::Texture &texture, int row, int frames, int fps) {
  framesPerSecond_ = fps;
  numberOfFrames_ = frames;

  for (int i = 0; i < numberOfFrames_; i++) {
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(i * 64, row * 64, 64, 64));
    sprites_.push_back(sprite);
  }
  currentSprite_ = &sprites_[0];
  currentFrame_ = 0;
}

Sprite Animation::getSprite() {
  return *currentSprite_;
}

void Animation::start() {
  clock.restart();
}

void Animation::stop() {
  //Stop timer
}

void Animation::update() {
  //Update current frame
  if (clock.getElapsedTime().asSeconds() > (1.0f/framesPerSecond_)) {
    clock.restart();
    currentSprite_ = &sprites_[currentFrame_++];
  }
  if (currentFrame_ > (numberOfFrames_ - 1)) {
    currentFrame_ = 0;
  }
}