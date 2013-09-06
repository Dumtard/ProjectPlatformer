#include "LoginState.h"

#include <iostream>

LoginState::LoginState(sf::RenderWindow &window, Network &network)
: GameState(window, network) {
  window_.setKeyRepeatEnabled(true);

  if (!font_.loadFromFile("fonts/arial.ttf")) {
    std::cout << "Did not load font";
  }

  text_.setFont(font_);
  text_.setColor(sf::Color(0, 0, 0));
  text_.setCharacterSize(20);
  text_.setPosition(10, 100);
}

LoginState::~LoginState() {

}

void LoginState::input() {
}

void LoginState::input(sf::Event event) {
  if (event.type == sf::Event::Closed) {
    network_.disconnect();
  } else if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Escape) {
      network_.disconnect();
    } else if (event.key.code == sf::Keyboard::BackSpace) {
      if (account_.size() > 0) {
        account_.erase(account_.size() - 1, 1);
      }
    }
  } else if (event.type == sf::Event::TextEntered) {
    if ((event.text.unicode >= 48 && event.text.unicode <= 57) ||
        (event.text.unicode >= 65 && event.text.unicode <= 90) ||
        (event.text.unicode >= 97 && event.text.unicode <= 122)) {
      account_ += static_cast<char>(event.text.unicode);
    } else if (event.text.unicode == 13) {
      network_.connect(account_);
      Application::getInstance().changeState(
          std::unique_ptr<GameState>(new MainState(
                                            window_, network_, account_)));
      //Send to server account
      //Get reply back
      //If good switch to MainState
      //Else do nothing


      // bool network_.connect() // revieve in connect return true/false
      // if true continue
      // else do nothing
    }
  }
}

void LoginState::update() {
  text_.setString(account_);
}

void LoginState::render(float delta) {
  window_.draw(text_);
}