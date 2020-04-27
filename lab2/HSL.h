#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Color.h"

class HSL : public Color {
public:
	HSL(float, float, float);

	void update(float, float, float) override;

	float getH() const;
	float getS() const;
	float getL() const;

	void setH(float);
	void setS(float);
	void setL(float);

private:
	void calcRGB();
	float HueToRGB(float, float, float);

	float _h{0};
	float _s{0};
	float _l{0};
};

