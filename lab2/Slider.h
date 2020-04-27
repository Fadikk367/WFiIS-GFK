#pragma once

#include<SFML/Graphics.hpp>

class Slider : public sf::Drawable {
public:
	Slider(sf::Vector2f, sf::Vector2i, float);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void update(int);

	void fillGradient(int, int);

	sf::Vector2f getPosition() const;

	sf::Vector2f getSize() const;

	~Slider();

private:
	sf::RectangleShape _slider;
	sf::RectangleShape _line;
	sf::Sprite* _sprite{ nullptr };
	sf::Uint8* _pixels{ nullptr };
	sf::Texture* _texture{ nullptr };
};

