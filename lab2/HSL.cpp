#include "HSL.h"

HSL::HSL(float h, float s, float l) : Color(0,0,0), _h(h), _s(s), _l(l) {
	calcRGB();
}

float HSL::getH() const {
	return _h;
}

float HSL::getS() const {
	return _s;
}

float HSL::getL() const {
	return _l;
}

void HSL::setH(float h) {
	_h = h;
	calcRGB();
}

void HSL::setS(float s) {
	_s = s;
	calcRGB();
}

void HSL::setL(float l) {
	_l = l;
	calcRGB();
}

void HSL::update(float byAngle, float byRadius, float bySliderValue) {
  _h = byAngle;
  _s = byRadius;
  _l = bySliderValue;
  calcRGB();
}

void HSL::calcRGB() {
  if (_s == 0) {
    _r = _l * 255;
    _g = _l * 255;
    _b = _l * 255;
  } else {
    float var1;
    float var2;
    if (_l < 0.5) var2 = _l * (1 + _s);
    else var2 = (_l + _s) - (_s * _l);

    var1 = 2 * _l - var2;

    _r =  (255 * HueToRGB(var1, var2, _h + (1.0 / 3)));
    _g =  (255 * HueToRGB(var1, var2, _h));
    _b =  (255 * HueToRGB(var1, var2, _h - (1.0 / 3)));
  }
}

float HSL::HueToRGB(float v1, float v2, float vH) {
  if (vH < 0) vH += 1;
  if (vH > 1) vH -= 1;
  if ((6 * vH) < 1) return (v1 + (v2 - v1) * 6 * vH);
  if ((2 * vH) < 1) return (v2);
  if ((3 * vH) < 2) return (v1 + (v2 - v1) * ((2.0 / 3) - vH) * 6);
  return (v1);
}