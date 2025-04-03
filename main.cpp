int const MAP_HEIGHT = 23;
int const MAP_WIDTH = 23;
int const CELLULE_SIZE = 25;

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include "pacman.h"
#include "ghost.h"

bool win(std::string map[MAP_HEIGHT])
{
  for (int i = 0; i < MAP_HEIGHT; i++)
  {
    for (int j = 0; j < MAP_WIDTH; j++)
    {
      if (map[i][j] == '.')
      {
        return false;
      }
    }
  }
  return true;
}

bool bonusPoint(std::string map[MAP_HEIGHT], int x, int y)
{
  if (map[y][x] == 'P')
  {
    return true;
  }
  return false;
}

int main()
{
  int SCORE = 0;
  char DIRECTION = ' ';

  sf::Font font;
  font.loadFromFile("pacman-art/arial.ttf");

  sf::Text text("You win!", font, 50);
  text.setFillColor(sf::Color::White);
  text.setPosition(300, 250);

  sf::Text scoreText("Score: 0", font, 20);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition(600, 10);
  Ghost ghost1(10, 10); // Exemple de position initiale
  Ghost ghost2(12, 12); // Un autre fantôme si nécessaire
  // Create the map
  std::string map[MAP_HEIGHT] = {
      "#######################",
      "#..........#..........#",
      "#.###.####.#.####.###.#",
      "#.....................#",
      "#.###.#.#######.#.###.#",
      "#.....#.#######.#.....#",
      "#####.#....#....#.#####",
      "#####.####.#.####.#####",
      "#####.#.........#.#####",
      "#####.#.###O###.#.#####",
      "L.......#12 34#.......R",
      "#####.#.#######.#.#####",
      "#####.#....P....#.#####",
      "#####.#.#######.#.#####",
      "#####.#.#######.#.#####",
      "#..........#..........#",
      "#.###.####.#.####.###.#",
      "#...#.............#...#",
      "###.#.#.#######.#.#.###",
      "#.....#....#....#.....#"
      "#.########.#.########.#",
      "#.########.#.########.#",
      "#C....................#",
      "#######################"};

  // create the window
  // Create all the entities
  sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
  // run the program as long as the window is open
  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
    }
    // clear the window with black color
    window.clear(sf::Color::Black);
    // draw the map
    // on créer chaque element de la map
    sf::RectangleShape rectangle(sf::Vector2f(CELLULE_SIZE, CELLULE_SIZE)); // les murs
    sf::CircleShape point(2.5f);                                            // les boules
    if (win(map) == false)
    {
      for (int i = 0; i < MAP_HEIGHT; i++)
      {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
          if (map[i][j] == '#')
          {
            rectangle.setPosition(j * CELLULE_SIZE, i * CELLULE_SIZE);
            rectangle.setFillColor(sf::Color::Blue);
            window.draw(rectangle);
          }
          if (map[i][j] == 'O')
          {
            rectangle.setPosition(j * CELLULE_SIZE, i * CELLULE_SIZE);
            rectangle.setFillColor(sf::Color::White);
            window.draw(rectangle);
          }
          if (map[i][j] == 'P')
          {
            Pacman pacman(j, i); // Create Pacman at the position of 'P'
            pacman.draw(window); // Draw Pacman
          }
          if (map[i][j] == '.')
          {
            point.setPosition(j * CELLULE_SIZE + 11.25, i * CELLULE_SIZE + 11.25);
            point.setFillColor(sf::Color::Yellow);
            window.draw(point);
          }
          if (map[i][j] == 'C')
          {
            rectangle.setPosition(j * CELLULE_SIZE, i * CELLULE_SIZE);
            rectangle.setFillColor(sf::Color::Red);
            window.draw(rectangle);
          }
        }
      }
      // Display the score
      scoreText.setString("Score: " + std::to_string(SCORE));
      window.draw(scoreText);

      // let's detect the pacman
      int pacmanX = 0; // Pacman's initial position
      int pacmanY = 0; // Pacman's initial position
      for (int i = 0; i < MAP_HEIGHT; i++)
      {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
          if (map[i][j] == 'P')
          {
            pacmanX = j;
            pacmanY = i;
          }
        }
      }
      // I want to make a little delay to see the pacman moving
      std::this_thread::sleep_for(std::chrono::milliseconds(75)); // 50 milliseconds delay
      // Move the pacman to the right
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && map[pacmanY][pacmanX + 1] != '#')
      {
        DIRECTION = 'R';
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && map[pacmanY][pacmanX - 1] != '#')
      {
        DIRECTION = 'L';
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && map[pacmanY - 1][pacmanX] != '#')
      {
        DIRECTION = 'U';
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && map[pacmanY + 1][pacmanX] != '#')
      {
        DIRECTION = 'D';
      }

      if (DIRECTION == 'R' && map[pacmanY][pacmanX + 1] != '#')
      {
        if (map[pacmanY][pacmanX + 1] == 'C')
        {
          SCORE += 500;                    // Increase the score
          map[pacmanY][pacmanX] = ' ';     // Clear the old position
          map[pacmanY][pacmanX + 1] = 'P'; // Move to the left
        }
        if (map[pacmanY][pacmanX + 1] == '.')
        {
          SCORE += 10;                     // Increase the score
          map[pacmanY][pacmanX] = ' ';     // Clear the old position
          map[pacmanY][pacmanX + 1] = 'P'; // Move to the left
        }
        if (map[pacmanY][pacmanX + 1] == 'R')
        {
          map[10][21] = ' '; // Clear the old position
          map[10][1] = 'P';  // Clear the old position
        }
        else
        {
          map[pacmanY][pacmanX] = ' ';     // Clear the old position
          map[pacmanY][pacmanX + 1] = 'P'; // Move to the right
        }
      }
      // movre pacman to the left
      if (DIRECTION == 'L' && map[pacmanY][pacmanX - 1] != '#')
      {
        if (map[pacmanY][pacmanX - 1] == 'C')
        {
          SCORE += 500;                    // Increase the score
          map[pacmanY][pacmanX] = ' ';     // Clear the old position
          map[pacmanY][pacmanX - 1] = 'P'; // Move to the left
        }
        if (map[pacmanY][pacmanX - 1] == '.')
        {
          SCORE += 10;                     // Increase the score
          map[pacmanY][pacmanX] = ' ';     // Clear the old position
          map[pacmanY][pacmanX - 1] = 'P'; // Move to the left
        }
        if (map[pacmanY][pacmanX - 1] == 'L')
        {
          map[10][1] = ' ';  // Clear the old position
          map[10][21] = 'P'; // Clear the old position
        }
        else
        {
          map[pacmanY][pacmanX] = ' ';     // Clear the old position
          map[pacmanY][pacmanX - 1] = 'P'; // Move to the left
        }
      }
      // Move the pacman up
      if (DIRECTION == 'U' && map[pacmanY - 1][pacmanX] != '#')
      {
        if (map[pacmanY - 1][pacmanX] == 'C')
        {
          SCORE += 500;                    // Increase the score
          map[pacmanY][pacmanX] = ' ';     // Clear the old position
          map[pacmanY - 1][pacmanX] = 'P'; // Move to the left
        }
        if (map[pacmanY - 1][pacmanX] == '.')
        {
          SCORE += 10;                     // Increase the score
          map[pacmanY][pacmanX] = ' ';     // Clear the old position
          map[pacmanY - 1][pacmanX] = 'P'; // Move to the left
        }
        else
        {
          map[pacmanY][pacmanX] = ' ';     // Clear the old position
          map[pacmanY - 1][pacmanX] = 'P'; // Move up
        }
      }
      // Move the pacman down
      if (DIRECTION == 'D' && map[pacmanY + 1][pacmanX] != '#' && map[pacmanY + 1][pacmanX] != 'O')
      {
        if (map[pacmanY + 1][pacmanX] == 'C')
        {
          SCORE += 500;                    // Increase the score
          map[pacmanY][pacmanX] = ' ';     // Clear the old position
          map[pacmanY + 1][pacmanX] = 'P'; // Move to the left
        }
        if (map[pacmanY + 1][pacmanX] == '.')
        {
          SCORE += 10;                     // Increase the score
          map[pacmanY][pacmanX] = ' ';     // Clear the old position
          map[pacmanY + 1][pacmanX] = 'P'; // Move to the left
        }
        else
        {
          map[pacmanY][pacmanX] = ' ';     // Clear the old position
          map[pacmanY + 1][pacmanX] = 'P'; // Move down
        }
      }
    }
    else
    {
      window.draw(text);

      // Display the score
      scoreText.setString("Score: " + std::to_string(SCORE));
      scoreText.setPosition(350, 350); // Position the score text
      window.draw(scoreText);
    }

    // Display the win message

    // end the current frame
    window.display();
  }
  return 0;
}

// prochaine etape :
// 1. faire le score : fait
// 2. faire le fantome
// 3. condition de defaite