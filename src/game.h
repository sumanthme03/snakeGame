#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "SDL_rect.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
//include libraries for mutex, condition_variableand thread
#include <mutex>
#include <condition_variable>
#include <thread>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  void PlaceFood();

  //new method to place food 1
  void PlaceFood1();

 private:
  Snake snake;
  SDL_Point food;

  //new SDL_Point food1
  SDL_Point food1;

  //new mutex and condition variable added for multithreading usecase
  std::mutex mutx;//added
  std::condition_variable _cond;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  /*void PlaceFood();*/
  void Update();

  // first food - x and  ycheck
  bool Food_Cell(int x, int y);
};

#endif