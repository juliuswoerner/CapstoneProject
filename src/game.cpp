#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceObjects();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, _food.getPosition(), _obstacle.getPosition());

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceObjects() {
  int x, y, xObstacle, yObstacle;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      _food.getPosition().x = x;
      _food.getPosition().y = y;
      while (true) {
        xObstacle = random_w(engine);
        yObstacle = random_h(engine);
        if (!_food.hitObject(xObstacle, yObstacle && !snake.SnakeCell(xObstacle, yObstacle))){
          _obstacle.getPosition().x = xObstacle;
          _obstacle.getPosition().y = yObstacle;
          return;
        }
      }
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (_food.isFood(new_x, new_y)) {
    IncreaseScore();
    PlaceObjects();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.IncreaseSpeed();
  }
  if (_obstacle.hitObstacle(new_x, new_y)){
    _obstacle.hitObstacle(snake);
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

bool Obstacle::hitObstacle(int x, int y){
  if (x == static_cast<int>(_position.x) && y == static_cast<int>(_position.y)) {
    return true;
  }
  return false;  
};

bool Food::isFood(int x, int y){
  if (x == static_cast<int>(_position.x) && y == static_cast<int>(_position._y)){
    return true;
  }
  return false;
};
