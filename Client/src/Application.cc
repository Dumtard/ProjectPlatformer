#include "Application.h"

#include <iostream>

Application::Application() {
  window.create(sf::VideoMode(800, 600), "Maplestory2", sf::Style::Close);
  if (!icon.loadFromFile("resources/Icon.png"))
    std::cout << "Failed to load Icon";

  window.setVerticalSyncEnabled(true);
  window.setKeyRepeatEnabled(false);
  window.setIcon(32, 32, icon.getPixelsPtr());

  elapsed = clock.restart().asSeconds();
  lag = 0.0f;

  framerate = 60;
  MS_PER_UPDATE = 1.0f / (float)framerate;

  state_ = std::unique_ptr<GameState>(new MainState(window));
}

Application::~Application() {
  // delete state_;
}

void Application::loop() {
  while (window.isOpen()) {
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
  while (window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape) {
          window.close();
        }
        break;

      default:
        break;
    }
    state_->input(event);
  }
}

void Application::update() {
  state_->update();
}

void Application::render(float delta) {
  window.clear(sf::Color(0, 200, 255));

  state_->render(delta);

  window.display();
}

void Application::setNetwork() {
  state_->setNetwork();
}

void Application::changeState(std::unique_ptr<GameState> state) {
  state_ = std::move(state);
}