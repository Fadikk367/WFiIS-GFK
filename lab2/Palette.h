#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "HSL.h"
#include "HSV.h"
#include "CMY.h"
#include <math.h>
#include "Color.h"

class Palette : sf::Drawable, sf::Transformable {
public:

	Palette(sf::Vector2f, float, std::string);

	void update(float);

	void draw(sf::RenderTarget&, sf::RenderStates states = sf::RenderStates::Default) const override;

	~Palette();

private:
	void fillPixelsColors();

	sf::Uint8* _pixels{nullptr};
	sf::Texture* _texture{nullptr};
	float _sliderValue{0.5};
	float _radius;
	int _size;
	Color* _color;
	sf::Vector2f _position;
	std::string _colorSystem;
	sf::Text* _name;
	sf::Text* _value;
	sf::Sprite* _sprite{ nullptr };
	sf::Font _font;
};

