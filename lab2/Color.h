#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Color {
public:
	Color(int r, int g, int b) : _r(r), _g(g), _b(b) {};
	virtual void update(float, float, float);

	sf::Uint8 getR() const;
	sf::Uint8 getG() const;
	sf::Uint8 getB() const;

	sf::Uint8 _r;
	sf::Uint8 _g;
	sf::Uint8 _b;
};

