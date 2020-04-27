#include "LineWrapper.h"

void LineWrapper::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*_line);
}

void LineWrapper::update(sf::Vector2i& start, sf::Vector2i& mouse) {
	(*_line)[1].position = sf::Vector2f(mouse);
}

LineWrapper::~LineWrapper() {
	delete _line;
}
