#pragma once
#include "Color.h"

class CMY : public Color {
public:
	CMY(float, float, float);

	void update(float, float, float) override;

	float getC() const;
	float getM() const;
	float getY() const;

	void setC(float);
	void setM(float);
	void setY(float);

private:
	void calcRGB();

	float _c{ 0 };
	float _m{ 0 };
	float _y{ 0 };
};

