#include "game.h"
#include <iostream>
#include "SDL.h"
#include "object.h"

bool Object::hitObject(int x, int y){
  if (x == static_cast<int>(_position.x) && y == static_cast<int>(_position._y)) {
    return true;
  }
  return false;  
};
