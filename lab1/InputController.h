#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Menu.h"

class InputController {
public:
  InputController(State& state, Menu& menu, sf::RenderWindow& window);

  sf::Event& getEvent();

  void handleKeyboardEvents();
  void handleMouseEvents();

private:

  sf::Event _event;
  State& _state;
  Menu& _menu;
  sf::RenderWindow& _window;

  void setMode(char c);

  void handleColorSelection();
};