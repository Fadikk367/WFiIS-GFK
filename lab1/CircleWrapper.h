#pragma once
#include "ShapeWrapper.h"
class CircleWrapper : public ShapeWrapper {
public:
	CircleWrapper() : _circle(nullptr) {};
	CircleWrapper(sf::CircleShape* circ) : _circle(circ) {};
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Vector2i&, sf::Vector2i&) override;

	~CircleWrapper() override;
private:
	sf::CircleShape* _circle;
};

