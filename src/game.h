#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Food 
{
  public:
    SDL_Point getPosition() {return _position; };
    void setPosition(int x, int y);
    bool isFood(int x, int y);

  private:
    SDL_Point _position;

};

class Obstacle
{
  public:
    SDL_Point getPosition() {return _position; };
    void setPosition(int x, int y);
    bool hitObstacle(int x, int y);
    void hitObstacle(Snake snake){ snake.alive = false; };

  private:
    SDL_Point _position;

};

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  void IncreaseScore();

 private:
  Snake snake;
  Food _food;
  Obstacle _obstacle;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceObjects();
  void Update();
};

#endif