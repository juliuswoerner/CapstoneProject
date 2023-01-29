#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "game.h"

class Object 
{

  public:
    SDL_Point getPosition(){ return _point; }
    bool hitObject(int x, int y);

  private:
    SDL_Point _point;

};

class Object : public Food 
{
  public:

  private:


};

class Object : public Obstacle
{
  public:
    void hitObstacle(Snake snake){ snake.alive = false; };

  private:

};