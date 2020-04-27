#include "CircleWrapper.h"

void CircleWrapper::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*_circle);
}

void CircleWrapper::update(sf::Vector2i& start, sf::Vector2i& mouse) {
	float radius = sqrtf(pow(mouse.x - start.x, 2) + pow(mouse.y - start.y, 2)) / 2.0;
	sf::Vector2f position(static_cast<float> (start.x) + static_cast<float> (mouse.x - start.x) / 2.f - radius, 
												static_cast<float> (start.y) + static_cast<float> (mouse.y - start.y) / 2.f - radius);
	_circle->setRadius(radius);
	_circle->setPosition(position);
}

CircleWrapper::~CircleWrapper() {
	delete _circle;
}
