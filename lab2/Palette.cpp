#include "Palette.h"

#include "font.h"

Palette::Palette(sf::Vector2f position, float radius, std::string colorSystem) : 
	_position(position), 
	_radius(radius), 
	_colorSystem(colorSystem) ,
  _size(2 * (static_cast<int> (radius)))
{
	_pixels = new sf::Uint8[_size * _size * 4]; // height = 2*radius, width = 2*radius, and 4 numbers for each pixel
	_texture = new sf::Texture();
	_sprite = new sf::Sprite();


  _font = sf::Font();
  _font.loadFromMemory(font_data, font_data_size);

  _name = new sf::Text();
  _value = new sf::Text();

  _name->setFont(_font);
  _value->setFont(_font);

  _name->setCharacterSize(14);
  _value->setCharacterSize(14);

  _name->setFillColor(sf::Color::Black);
  _value->setFillColor(sf::Color::Black);

  _name->setPosition(position);
  _value->setPosition(position + sf::Vector2f(180, 180));
  
  _name->setString(colorSystem);

  if (colorSystem == "HSL") {
    _color = new HSL(1.f, 1.f, 1.f);
    _value->setString(L"Y=" + sf::String(std::to_string(static_cast<int> (_sliderValue))));
  }
  else if (colorSystem == "RGB") {
    _color = new Color(100, 255, 50);
    _value->setString(L"B = " + sf::String(std::to_string(static_cast<int> (_sliderValue * 255))));
  }
  else if (colorSystem == "HSV") {
    _color = new HSV(1.f, 1.f, 1.f);
    _value->setString(L"V = " + sf::String(std::to_string(static_cast<int> (_sliderValue))));
  }
  else if (colorSystem == "CMY") {
    _color = new CMY(1.f, 1.f, 1.f);
    _value->setString(L"Y = " + sf::String(std::to_string(static_cast<int> (_sliderValue * 100))) + L"%");
  }

 
  _texture->create(_size, _size);
  _texture->update(_pixels);
  _sprite->setPosition(_position);
  _sprite->setTexture(*_texture);

  update(_sliderValue);
}


void Palette::update(float sliderValue) {
  _sliderValue = sliderValue;

  if (_colorSystem == "HSL") {
    _value->setString(L"L = " + sf::String(std::to_string(static_cast<float> (_sliderValue))).substring(0, 5));
  }
  else if (_colorSystem == "RGB") {
    _value->setString(L"B = " + sf::String(std::to_string(static_cast<int> (_sliderValue * 255))));
  }
  else if (_colorSystem == "HSV") {
    _value->setString(L"V = " + sf::String(std::to_string(static_cast<float> (_sliderValue))).substring(0, 5));
  }
  else if (_colorSystem == "CMY") {
    _value->setString(L"Y = " + sf::String(std::to_string(static_cast<int> (_sliderValue * 100))) + L"%");
  }

  fillPixelsColors();
	_texture->update(_pixels);
}

void Palette::fillPixelsColors() {
  for (int y = 0; y < _size; y++) {
    for (int x = 0; x < _size; x++) {
      float radius = sqrt(pow(_radius - x, 2) + pow(_radius - y, 2));
      float angle = asin((abs(y - _radius)) / radius) * 180.0 / 3.14159;
      if (x <= _radius && y <= _radius) {
        angle = 180 - angle;
      }
      else if (x <= _radius && y > _radius) {
        angle += 180;
      }
      else if (x > _radius && y >= _radius) {
        angle = 360 - angle;
      }
      _color->update(angle / 360.0, radius / _radius, _sliderValue);
      if (radius < _radius) {
        
        _pixels[4 * _size * y + x * 4] = _color->getR(); // RED        
        _pixels[4 * _size * y + x * 4 + 1] = _color->getG(); // GREEN
        _pixels[4 * _size * y + x * 4 + 2] = _color->getB(); // BLUE
        _pixels[4 * _size * y + x * 4 + 3] = 255; // ALPHA
      }
      else {
        _pixels[4 * _size * y + x * 4] = 255;
        _pixels[4 * _size * y + x * 4 + 1] = 255;
        _pixels[4 * _size * y + x * 4 + 2] = 255;
        _pixels[4 * _size * y + x * 4 + 3] = 255;
      }
    }
  }
}

void Palette::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*_sprite);
  target.draw(*_name);
  target.draw(*_value);
}

Palette::~Palette() {
  delete _sprite;
  delete _value;
  delete _name;
  delete _color;
  delete _texture;
  delete _pixels;
}