#include "InputController.h"


InputController::InputController(State& state, Menu& menu, sf::RenderWindow& window) :
  _state(state),
  _menu(menu),
  _window(window),
  _event(sf::Event()) {};

void InputController::handleKeyboardEvents() {
  if (_event.type == sf::Event::KeyPressed) {
    switch (_event.key.code) {
      case sf::Keyboard::F:
        setMode('f');
        break;
      case sf::Keyboard::B:
        setMode('b');
        break;
      case sf::Keyboard::L:
        setMode('l');
        break;
      case sf::Keyboard::R:
        setMode('r');
        break;
      case sf::Keyboard::A:
        setMode('a');
        break;
      case sf::Keyboard::C:
        setMode('c');
        break;
      case sf::Keyboard::W:
        setMode('w');
        _state.saveToFile();
        break;
      case sf::Keyboard::O:
        setMode('o');
        _state.deleteBuffer();
        _state.loadFromFile();
        break;
      case sf::Keyboard::Escape:
        _window.close();
        break;
      default:
        break;
    }
  }
}

void InputController::handleMouseEvents() {
  if (_event.type == sf::Event::Closed)
    _window.close();
  else if (_event.type == sf::Event::MouseButtonPressed) {
    if (_event.mouseButton.x < 765 && _event.mouseButton.y < 60) handleColorSelection();
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
             !_state.isDrawing && 
             _state.mode != 'b' && 
             _state.mode != 'f') {
      _state.startDrawing(sf::Mouse::getPosition(_window));
    }
  }
  else if ((_event.type == sf::Event::MouseButtonReleased) && 
           (_event.mouseButton.button == sf::Mouse::Left)) {
    _state.finishDrawing();
  }
  else if ((_event.type == sf::Event::MouseMoved) && 
            sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
            _state.isDrawing) {
    _state.keepDrawing(sf::Mouse::getPosition(_window));
  }
}

void InputController::handleColorSelection() {
  sf::Color pickedColor = _menu.getColor(_event.mouseButton.x, _event.mouseButton.y);
  if (_state.mode == 'f') {
    _state.setPickedColor(pickedColor);
    _menu.setPickedColor(pickedColor);
  }
  else if (_state.mode == 'b') {
    _state.setFillColor(pickedColor);
    _menu.setFillColor(pickedColor);
  }
}

void InputController::setMode(char mode) {
  _state.setMode(mode);
  _menu.setMode(mode);
}

sf::Event& InputController::getEvent() {
  return _event;
}
