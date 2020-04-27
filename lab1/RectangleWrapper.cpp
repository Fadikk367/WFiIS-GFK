#include "RectangleWrapper.h"

void RectangleWrapper::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*_rect);
}

void RectangleWrapper::update(sf::Vector2i& start, sf::Vector2i& mouse)  {
	sf::Vector2f size(mouse.x - start.x, mouse.y - start.y);
	_rect->setSize(size);
}

RectangleWrapper::~RectangleWrapper() {
	delete _rect;
}