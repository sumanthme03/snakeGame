#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) 
{
  PlaceFood();
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
    renderer.Render(snake, food,food1); //food to be used to render 

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

void Game::PlaceFood() {
	//Lock the thread - use lock_gaurd
	std::lock_guard<std::mutex> uLock(mutx);
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
	  //at this point notify other thread
	  _cond.notify_one();
      return;
    }
  }
}

void Game::PlaceFood1() {
  //use unique_lock to lock 
  std::unique_lock<std::mutex> uLock(mutx);
  
  // use of condition variable to wait until another thread modifies a shared variable
  //check if first food is set  
  _cond.wait(uLock, [this] (){ return (food.x != -1 && food.y != -1) ? true : false; });

  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
   // Check that the location is not occupied by a snake item and the first
    //food item before placing the second food
    if (!snake.SnakeCell(x, y) && !Food_Cell(x, y)) {
      food1.x = x;
      food1.y = y;
      return;
    }
  }
}



void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (   food.x == new_x && food.y == new_y
      || food1.x == new_x && food1.y == new_y) 
  {
    score++;
    //PlaceFood();
    // Grow snake and increase speed.
	
	  food.x = -1;
      food.y = -1;
      food1.x = -1;
      food1.y = -1;
	  
    //use threads , Call functions PlaceFood and PlaceFood1 
    std::thread t1(&Game::PlaceFood, this);
    std::thread t2(&Game::PlaceFood1, this);
	
    //join the threads back to the main function
    t1.join();
    t2.join();
	
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

bool Game::Food_Cell(int x, int y) 
{
  if (x == static_cast<int>(food.x) && y == static_cast<int>(food.y)) 
  {
    return true;
  }
  return false;
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }