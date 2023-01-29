#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  void IncreaseScore();

 private:
  Snake _snake;
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

class Object 
{

  public:
    SDL_Point getPosition(){ return _position; }
    bool hitObject(int x, int y);

  private:
    SDL_Point _point;

}

class Object : public Food 
{

  public:

  private:


}

class Object : public Obstacle
{

  public:
    void hitObstacle(Snake snake){ snake.alive = false; };

  private:

}

#endif