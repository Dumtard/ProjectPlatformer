#include "Application.h"

#include <iostream>

 void Application::initialize() {
  window_.create(sf::VideoMode(800, 600), "Client", sf::Style::Close);
  if (!icon_.loadFromFile("resources/Icon.png"))
    std::cout << "Failed to load Icon";

  window_.setVerticalSyncEnabled(true);
  window_.setKeyRepeatEnabled(false);
  window_.setIcon(32, 32, icon_.getPixelsPtr());

  elapsed = clock.restart().asSeconds();
  lag = 0.0f;

  framerate = 60;
  MS_PER_UPDATE = 1.0f / (float)framerate;

  state_ = std::unique_ptr<GameState>(new LoginState(window_, network_));
}

Application::~Application() {
  // delete state_;
}

void Application::loop() {
  while (window_.isOpen()) {
    elapsed = clock.restart().asSeconds();
    lag += elapsed;

    getNetwork();

    input();

    while (lag >= MS_PER_UPDATE) {
      update();
      lag -= MS_PER_UPDATE;
    }
    render(lag / MS_PER_UPDATE);

    setNetwork();

    // std::cout << "FPS: " + std::to_string(1 / elapsed) << std::endl;
  }
}

void Application::getNetwork() {
  state_->getNetwork();
}

void Application::input() {
  state_->input();
  while (window_.pollEvent(event_)) {
    switch (event_.type) {
      case sf::Event::Closed:
        window_.close();
        break;

      case sf::Event::KeyPressed:
        if (event_.key.code == sf::Keyboard::Escape) {
          window_.close();
        }
        break;

      default:
        break;
    }
    state_->input(event_);
  }
}

void Application::update() {
  state_->update();
}

void Application::render(float delta) {
  window_.clear(sf::Color(0, 200, 255));

  state_->render(delta);

  window_.display();
}

void Application::setNetwork() {
  state_->setNetwork();
}

void Application::changeState(std::unique_ptr<GameState> state) {
  state_ = std::move(state);
}