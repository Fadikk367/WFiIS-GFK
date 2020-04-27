#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Menu : public sf::Drawable {
public:
  Menu();

  void setMode(char c);

  void setPickedColor(sf::Color color);

  void setFillColor(sf::Color color);

  sf::Color getColor(int x, int y);

  void outtextxy(sf::RenderTarget& target, float x, float y, wchar_t* str) const;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
  sf::Font font;
  sf::Text* text;
  sf::RectangleShape* rectangle;

  sf::Texture* colors_texture;
  sf::Sprite* colors_sprite;
  sf::Uint8* colors_pixels;
  const unsigned int colors_size_x = 765;
  const unsigned int colors_size_y = 60;

  // mine
  sf::Image* colorBar;
  sf::RectangleShape* modeCleaner;
  sf::RectangleShape* colorRect;
  sf::RectangleShape* fillColorRect;
  char mode{ ' ' };

  inline void draw_to_color_pixels(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b);
};