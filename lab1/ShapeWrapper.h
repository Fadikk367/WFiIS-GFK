#pragma once
#include <SFML/Graphics.hpp>

class ShapeWrapper : public sf::Drawable, public sf::Transformable {
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void update(sf::Vector2i&, sf::Vector2i&) = 0;
	virtual ~ShapeWrapper() = default;
};

