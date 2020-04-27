#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>

#include "Slider.h"
#include "Palette.h"

class InputController {
public:
	InputController(sf::RenderWindow&, Slider&, std::vector<Palette*>);
	void handleMouseEvent();
	sf::Event& getEvent();

private:
	bool _isIndicatorActive;
	sf::Event _event;
	Slider& _sliderRef;
	sf::Vector2f _sliderPos;
	sf::Vector2f _sliderSize;
	std::vector<Palette*> _vec;
	sf::RenderWindow& _windowRef;
};

