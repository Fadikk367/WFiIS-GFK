#include "HSV.h"


HSV::HSV(float h, float s, float v) : Color(0, 0, 0), _h(h), _s(s), _v(v) {
  calcRGB();
}

float HSV::getH() const {
  return _h;
}

float HSV::getS() const {
  return _s;
}

float HSV::getV() const {
  return _v;
}

void HSV::setH(float h) {
  _h = h;
  calcRGB();
}

void HSV::setS(float s) {
  _s = s;
  calcRGB();
}

void HSV::setV(float v) {
  _v = v;
  calcRGB();
}

void HSV::update(float byAngle, float byRadius, float bySliderValue) {
  _h = byAngle;
  _s = byRadius;
  _v = bySliderValue;
  calcRGB();
}

void HSV::calcRGB() {
  if (_s == 0) {
    _r = _v * 255;
    _g = _v * 255;
    _b = _v * 255;
  }
  else {
    float varH = _h * 6;
    if (abs(varH - 6) < 0.00001) varH = 0;     
    int varI = (int) varH;
    float var1 = _v * (1 - _s);
    float var2 = _v * (1 - _s * (varH - varI));
    float var3 = _v * (1 - _s * (1 - (varH - varI)));

    float varR;
    float varG;
    float varB;
    if (varI == 0) { varR = _v; varG = var3; varB = var1; }
    else if (varI == 1) { varR = var2; varG = _v; varB = var1; }
    else if (varI == 2) { varR = var1; varG = _v; varB = var3; }
    else if (varI == 3) { varR = var1; varG = var2; varB = _v; }
    else if (varI == 4) { varR = var3; varG = var1; varB = _v; }
    else { varR = _v; varG = var1; varB = var2; }

    _r = varR * 255;
    _g = varG * 255;
    _b = varB * 255;
  }
}
