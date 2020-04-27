#include "State.h"


State::State() {
  finalSprite.setPosition(1, 63);
  buffer.create(796, 536);
}

void State::drawBuffer() {
  buffer.clear(sf::Color::Black);
  if (background != nullptr) {
    buffer.draw(*background);
  }
  for (const auto* obj : objects) {
    buffer.draw(*obj);
  }
  if (current != nullptr)
    buffer.draw(*current);
}

void State::deleteBuffer() {
  for (const auto* obj : objects) {
    delete obj;
  }
  objects.resize(0, nullptr);
  delete current;
  current = nullptr;
}

void State::setMode(char c) {
  mode = c;
}

void State::clearBuffer() {
  buffer.clear(sf::Color::Black);
}

void State::render() {
  drawBuffer();
  buffer.display();
  finalSprite.setTexture(buffer.getTexture());
}

void State::setPickedColor(sf::Color color) {
  pickedColor = color;
}

void State::setFillColor(sf::Color color) {
  fillColor = color;
}

void State::startDrawing(sf::Vector2i& pos) {
  sf::Vector2f fixedPos = sf::Vector2f(pos.x - 1, pos.y - 63);
  isDrawing = true;
  startPosition = sf::Vector2i(pos.x - 1, pos.y - 63);
  if (mode == 'r') {
    sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f());
    rect->setPosition(fixedPos);
    rect->setFillColor(sf::Color::Transparent);
    rect->setOutlineColor(pickedColor);
    rect->setOutlineThickness(1.f);
    current = new RectangleWrapper(rect);
  }
  else if (mode == 'c') {
    sf::CircleShape* circle = new sf::CircleShape();
    circle->setPosition(fixedPos);
    circle->setFillColor(sf::Color::Transparent);
    circle->setOutlineColor(pickedColor);
    circle->setOutlineThickness(1.f);
    current = new CircleWrapper(circle);
  }
  else if (mode == 'l') {
    sf::VertexArray* line = new sf::VertexArray(sf::LinesStrip, 2);
    (*line)[0].position = sf::Vector2f(fixedPos);
    (*line)[1].position = sf::Vector2f(fixedPos);
    (*line)[0].color = pickedColor;
    (*line)[1].color = fillColor;
    current = new LineWrapper(line);
  }
  else if (mode == 'a') {
    sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f());
    rect->setPosition(fixedPos);
    rect->setFillColor(fillColor);
    rect->setOutlineColor(pickedColor);
    rect->setOutlineThickness(1.f);
    current = new RectangleWrapper(rect);
  }
  else {
    isDrawing = false;
  }
}

void State::keepDrawing(sf::Vector2i& pos) {
  if (isDrawing && current != nullptr) {
    current->update(startPosition, sf::Vector2i(pos.x - 1, pos.y - 63));
  }
}

void State::finishDrawing() {
  if (isDrawing) {
    isDrawing = false;
    objects.emplace_back(current);
    current = nullptr;
  }
}

void State::saveToFile() {
  buffer.getTexture().copyToImage().saveToFile("./result.png");
}

void State::loadFromFile() {
  if (backgroundFromFile.loadFromFile("./result.png")) {
    background = new sf::Sprite();
    background->setTexture(backgroundFromFile);
    std::cout << "wczytane tlo z pliku" << std::endl;
  }
  else {
    std::cout << "Blad podczas wczytywania tla z pliku" << std::endl;
  }
}

State::~State() {
  clearBuffer();
  delete background;
  delete current;
}

