#pragma once

#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "ShapeWrapper.h"
#include "RectangleWrapper.h"
#include "CircleWrapper.h"
#include "LineWrapper.h"


struct State {
  bool isDrawing{ false };
  char mode{ ' ' };

  sf::Vector2i startPosition;
  sf::Sprite finalSprite;

  ShapeWrapper* current{ nullptr };
  std::vector<ShapeWrapper*> objects;
  sf::Sprite* background{ nullptr };

  sf::Color pickedColor{ sf::Color::Black };
  sf::Color fillColor{ sf::Color::Black };

  sf::Texture backgroundFromFile;
  sf::RenderTexture buffer;

  
  State();

  void drawBuffer();

  void render();

  void clearBuffer();

  void deleteBuffer();

  void setMode(char c);

  void setPickedColor(sf::Color color);

  void setFillColor(sf::Color color);

  void startDrawing(sf::Vector2i& pos);

  void keepDrawing(sf::Vector2i& pos);

  void finishDrawing();

  void saveToFile();

  void loadFromFile();

  ~State();
};