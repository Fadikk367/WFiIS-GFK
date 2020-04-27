#include "InputController.h"

InputController::InputController(sf::RenderWindow& window, Slider& slider, std::vector<Palette*> vec) :
  _isIndicatorActive(false),
	_windowRef(window),  
	_sliderRef(slider),
	_vec(vec)
{
	_event = sf::Event();
  _sliderPos = _sliderRef.getPosition();
  _sliderSize = _sliderRef.getSize();
}

void InputController::handleMouseEvent() {
  if (_event.type == sf::Event::Closed)
    _windowRef.close();
  else if (_isIndicatorActive && _event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    const sf::Vector2i mouse = sf::Mouse::getPosition(_windowRef);
    if (
      ((mouse.x > _sliderPos.x && mouse.x < _sliderPos.x + _sliderSize.x) &&
      (mouse.y > _sliderPos.y && mouse.y < _sliderPos.y + _sliderSize.y)))
    {
      //std::cout << "moving..." << std::endl;
      for (auto* item : _vec)
        item->update((static_cast<float> (mouse.y) - _sliderPos.y) / _sliderSize.y);
      _sliderRef.update(mouse.y);
    }
  }
  else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !_isIndicatorActive) {
    const sf::Vector2i mouse = sf::Mouse::getPosition(_windowRef);
    if (
      ((mouse.x >= _sliderPos.x && mouse.x <= _sliderPos.x + _sliderSize.x) &&
      (mouse.y >= _sliderPos.y && mouse.y <= _sliderPos.y + _sliderSize.y)))
    {
      //std::cout << "click - start" << std::endl;
      _isIndicatorActive = true;
      for (auto* item : _vec)
        item->update((static_cast<float> (mouse.y) - _sliderPos.y) / _sliderSize.y);
      _sliderRef.update(mouse.y);
    }
  }
  else if (_event.type == sf::Event::MouseButtonReleased && _isIndicatorActive) {
    //std::cout << "released - finish" << std::endl;
    _isIndicatorActive = false;
  }
}

sf::Event& InputController::getEvent() {
	return _event;
}