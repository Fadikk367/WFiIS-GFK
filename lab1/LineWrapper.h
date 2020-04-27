#pragma once
#include "ShapeWrapper.h"

class LineWrapper : public ShapeWrapper {
public:
	LineWrapper() : _line(nullptr) {};
	LineWrapper(sf::VertexArray* line) : _line(line) {};
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Vector2i&, sf::Vector2i&) override;

	~LineWrapper() override;
private:
	sf::VertexArray* _line;
};

