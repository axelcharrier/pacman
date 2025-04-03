#include <SFML/Graphics.hpp>

class Pacman
{
public:
  Pacman(int x, int y) : x(x), y(y) {}

  void draw(sf::RenderWindow &window)
  {
    sf::CircleShape pacman(12.5f);
    pacman.setFillColor(sf::Color::Yellow);
    pacman.setPosition(x * CELLULE_SIZE, y * CELLULE_SIZE);
    window.draw(pacman);
  }

  int getX() const { return x; }
  int getY() const { return y; }

private:
  int x;
  int y;
};