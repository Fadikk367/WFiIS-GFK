#include "Slider.h"
#include <iostream>

Slider::Slider(sf::Vector2f pos, sf::Vector2i size, float initialState) {
	_slider = sf::RectangleShape(sf::Vector2f(size));
	_slider.setPosition(pos);
	_slider.setOutlineColor(sf::Color(127, 127, 127, 255));
	_slider.setOutlineThickness(2);

	_line = sf::RectangleShape(sf::Vector2f(size.x + 20, 4));
	_line.setPosition(pos.x - 10, pos.y + size.y / 2 - 2);
	_line.setFillColor(sf::Color::Black);

	_pixels = new sf::Uint8[size.x * size.y * 4];
	_texture = new sf::Texture();
	_sprite = new sf::Sprite();

	fillGradient(size.x, size.y);

	_texture->create(size.x, size.y);
	_texture->update(_pixels);
	_sprite->setPosition(pos);
	_sprite->setTexture(*_texture);
}

void Slider::fillGradient(int width, int height) {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
			int color = 255 * ( static_cast<float> (y) / height);   
			_pixels[4 * width * y + x * 4] = color; // RED    
			_pixels[4 * width * y + x * 4 + 1] = color; // GREEN      
			_pixels[4 * width * y + x * 4 + 2] = color; // BLUE
      _pixels[4 * width * y + x * 4 + 3] = 255; // ALPHA
    }
  }
}


void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_line);
	target.draw(_slider);
	target.draw(*_sprite);
}

void Slider::update(int mouseClickPos) {
	_line.setPosition(_line.getPosition().x, mouseClickPos - 2);
}

sf::Vector2f Slider::getPosition() const {
	return _slider.getPosition();
}

sf::Vector2f Slider::getSize() const {
	return _slider.getSize();
}

Slider::~Slider() {
	delete _texture;
	delete _pixels;
	delete _sprite;
}
