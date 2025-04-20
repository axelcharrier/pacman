#include <SFML/Graphics.hpp>
#include <random>

class Ghost
{
private:
  int posX;
  int posY;
  int previousDirection = -1; // -1 signifie aucune direction précédente

public:
  Ghost(int x, int y) : posX(x), posY(y) {}

  int getX() const { return posX; } // Getter pour la position X
  int getY() const { return posY; } // Getter pour la position Y

  void draw(sf::RenderWindow &window, const std::string &color)
  {
    sf::CircleShape ghostShape(12.5f); // Create a circle shape for the ghost
    if (color == "red")
      ghostShape.setFillColor(sf::Color::Red); // Set the color of the ghost to red
    else if (color == "blue")
      ghostShape.setFillColor(sf::Color::Blue); // Set the color of the ghost to blue
    else if (color == "green")
      ghostShape.setFillColor(sf::Color::Green); // Set the color of the ghost to green

    ghostShape.setPosition(posX * CELLULE_SIZE, posY * CELLULE_SIZE);
    window.draw(ghostShape); // Draw the ghost
  }

  void teleport(int x, int y, std::string map[MAP_HEIGHT])
  {
    // Effacez l'ancienne position du fantôme dans la carte
    map[posY][posX] = ' ';

    // Mettez à jour les coordonnées du fantôme
    posX = x;
    posY = y;

    // Placez le fantôme à la nouvelle position dans la carte
    map[posY][posX] = '1'; // Assurez-vous que '1' correspond au fantôme
  }

  void move(int direction, std::string map[MAP_HEIGHT])
  {
    previousDirection = direction; // Store the previous direction
    switch (direction)
    {
    case 0: // Up
      posY--;
      break;
    case 1: // Down
      posY++;
      break;
    case 2: // Left
      posX--;
      break;
    case 3: // Right
      posX++;
      break;
    default:
      break;
    }

    // Ensure the ghost stays within the bounds of the grid
    if (posX < 0)
      posX = 0;
    if (posX >= MAP_WIDTH)
    {
      posX = MAP_WIDTH - 1;
    }
    if (posY < 0)
    {
      posY = 0;
    }
    if (posY >= MAP_HEIGHT)
    {
      posY = MAP_HEIGHT - 1;
    }

    // Ensure the ghost doesn't move through walls
    if (map[posY][posX] == '#' || map[posY][posX] == 'O' || map[posY][posX] == 'L' || map[posY][posX] == 'R')
    {
      // Move back to the previous position
      switch (direction)
      {
      case 0: // Up
        posY++;
        break;
      case 1: // Down
        posY--;
        break;
      case 2: // Left
        posX++;
        break;
      case 3: // Right
        posX--;
        break;
      default:
        break;
      }
    }
  }

  int getPreviousDirection() const
  {
    return previousDirection;
  }
};