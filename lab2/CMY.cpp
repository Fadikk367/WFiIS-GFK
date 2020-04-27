#include "CMY.h"

CMY::CMY(float c, float m, float y) : Color(0, 0, 0), _c(c), _m(m), _y(y) {};

void CMY::update(float byAngle, float byRadius, float bySliderValue) {
	_c = byRadius;
	_m = byAngle;
	_y = bySliderValue;
	calcRGB();
}

float CMY::getC() const {
	return _c;
}

float CMY::getM() const {
	return _m;
}

float CMY::getY() const {
	return _y;
}

void CMY::setC(float c) {
	_c = c;
	calcRGB();
}

void CMY::setM(float m ) {
	_m = m;
	calcRGB();
}

void CMY::setY(float y) {
	_y = y;
	calcRGB();
}


void CMY::calcRGB() {
	_r = (1.0 - _c) * 255;
	_g = (1.0 - _m) * 255;
	_b = (1.0 - _y) * 255;
}
