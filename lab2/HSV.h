#pragma once
#include "Color.h"

class HSV : public Color {
public:
	HSV(float, float, float);

	void update(float, float, float) override;

	float getH() const;
	float getS() const;
	float getV() const;

	void setH(float);
	void setS(float);
	void setV(float);

private:
	void calcRGB();

	float _h{ 0 };
	float _s{ 0 };
	float _v{ 0 };
};

