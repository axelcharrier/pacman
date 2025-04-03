#include <SFML/Graphics.hpp>
#include <random>

class Ghost
{
public:
  Ghost(int x, int y) : posX(x), posY(y) {}

  void draw(sf::RenderWindow &window, const std::string &color)
  {
    sf::CircleShape ghostShape(12.5f);
    ghostShape.setPosition(posX * CELLULE_SIZE, posY * CELLULE_SIZE);

    if (color == "red")
      ghostShape.setFillColor(sf::Color::Red);
    else if (color == "blue")
      ghostShape.setFillColor(sf::Color::Blue);
    else if (color == "green")
      ghostShape.setFillColor(sf::Color::Green);
    else if (color == "white")
      ghostShape.setFillColor(sf::Color::White);

    window.draw(ghostShape);
  }

  void move(std::string map[MAP_HEIGHT])
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dir(0, 3); // 0: up, 1: down, 2: left, 3: right

    int newX = posX;
    int newY = posY;

    switch (dir(gen))
    {
    case 0:
      newY--;
      break; // Up
    case 1:
      newY++;
      break; // Down
    case 2:
      newX--;
      break; // Left
    case 3:
      newX++;
      break; // Right
    }

    // Check if the new position is valid
    if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT && map[newY][newX] != '#')
    {
      posX = newX;
      posY = newY;
    }
  }

  int getX() const { return posX; }
  int getY() const { return posY; }

private:
  int posX;
  int posY;
};