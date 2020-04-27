#include "Color.h"

void Color::update(float byAngle, float byRadius, float bySliderValue) {
	_r = byRadius * 255;
	_g = byAngle * 255;
	_b = bySliderValue * 255;
}

sf::Uint8 Color::getR() const {
	return _r;
}

sf::Uint8 Color::getG() const {
	return _g;
}

sf::Uint8 Color::getB() const {
	return _b;
}
