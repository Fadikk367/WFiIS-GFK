#include "main.h"

int main(void) {
  sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 01", sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(60);

  Menu menu;
  State state;
  InputController input(state, menu, window);

  while (window.isOpen()) { 
    while (window.pollEvent(input.getEvent())) {
       input.handleKeyboardEvents();
       input.handleMouseEvents();
    }
    state.clearBuffer();

    state.render();
    window.draw(state.finalSprite);
    window.draw(menu);

    window.display();
  }
 return 0;
}