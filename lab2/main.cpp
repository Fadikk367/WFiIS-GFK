#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <math.h>
#include <vector>
#include <iostream>
#include <string>

#include "Slider.h"
#include "InputController.h"
#include "Palette.h"
#include "Color.h"

#include "font.h" 


int main()
{
  sf::Clock clock;
  sf::Time time = sf::Time::Zero;
  unsigned int FPS = 0, frame_counter = 0;
  sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close);

  // Font & text stuff
  sf::Font font;
  sf::Text* text;
 if (!font.loadFromMemory(font_data, font_data_size)) {
  std::cout << "failed to load font" << std::endl;
  }
  text = new sf::Text;
  text->setFont(font);
  text->setCharacterSize(14);
  text->setFillColor(sf::Color::Black);
  
  // Objects

  Slider slider(sf::Vector2f(700, 25), sf::Vector2i(60, 500), 0.5);
  std::vector<Palette*> objects;
  Palette* palette1 = new Palette(sf::Vector2f(50, 50), 100, "HSL");
  Palette* palette2 = new Palette(sf::Vector2f(350, 50), 100, "HSV");
  Palette* palette3 = new Palette(sf::Vector2f(50, 300), 100, "CMY");
  Palette* palette4 = new Palette(sf::Vector2f(350, 300), 100, "RGB");
  objects.emplace_back(palette1);
  objects.emplace_back(palette2);
  objects.emplace_back(palette3);
  objects.emplace_back(palette4);

  InputController input(window, slider, objects);

  //inicjalizacja 
  clock.restart().asMilliseconds();
  while (window.isOpen())
  {
    window.clear(sf::Color::White);

    while (window.pollEvent(input.getEvent()))
    {
      input.handleMouseEvent();
    }
    //tu wyrysowaæ wszystko na ekran

    //tu wypisaæ na ekran wartoœæ FPS
    if (clock.getElapsedTime().asSeconds() >= 1.0f)
    {
      FPS = (unsigned int)((float)frame_counter / clock.getElapsedTime().asSeconds());
      text->setPosition(690, 550);
      text->setString(std::string("FPS: ") + std::to_string(FPS));
      clock.restart();
      frame_counter = 0;
    }
    frame_counter++;
    window.draw(slider);
    for (const auto* obj : objects)
      obj->draw(window);
    window.draw(*text);
    window.display();
  }
  for (const auto* obj : objects)
    delete obj;
  delete text;
  return 0;
}