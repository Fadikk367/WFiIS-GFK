#pragma once
#include "ShapeWrapper.h"

class RectangleWrapper : public ShapeWrapper {
public:
	RectangleWrapper() : _rect(nullptr) {};
	RectangleWrapper(sf::RectangleShape* rect) : _rect(rect) {};
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Vector2i&, sf::Vector2i&) override;

	~RectangleWrapper();

private:
	sf::RectangleShape* _rect;
};

