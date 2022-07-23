#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

/*FUnction call sequences - 
a.Input_Game();
b.Scoresort();
c.Evaluate();
d.DisplayScore();
d.Output() - in main()*/

//save all of the scores in to vector of strings 
std::vector<std::string> every_scores;
void Scoresort();

//new function to read in Input_Game from "saved.txt"
void Input_Game()
{
  std::cout << "Previous scores are: " << std::endl;
  std::fstream scores;//create  object with fstream
  scores.open("saved.txt", std::ios::in);//read in  data from an external file
  if(scores.is_open()) 
  {
  	std::string line;
    while(getline(scores, line)) 
	{
    	every_scores.emplace_back(line);//save each scores in the vector every_scores
    }
    scores.close();
  }
  Scoresort();//call the Scoresort function
}

//for every score in every_scores print it to the console on its own line
void DisplayScore()
{
	for(auto &in: every_scores)
	{
    	std::cout << in << std::endl;
    }
}

//evaluate which score is high
bool Evaluate(std::string a1, std::string a2) 
{
	if(a1.size() == a2.size()) 
	{
		return a1 > a2;
    }
  	else 
	{
  		return a1.size() > a2.size();
  	}
}

//Sort scores from the beginning to the end of the every_scores vector
//following to that call the DisplayScore function
void Scoresort()
{
	std::sort(every_scores.begin(), every_scores.end(), Evaluate);
  	DisplayScore();
}

//write to the "saved.txt" file in append mode to add the new score in
void Output(std::string score)
{
  std::fstream output;//fstream object created
  output.open("saved.txt", std::ios::app);//open in append mode
  if(output.is_open()) 
  {
	output << score;//pass the score to output
    output.close();
  }
}

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  
  //function to fetch the previous saved scores
  Input_Game();
  
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  
  //string variable used to save the score 
  std::string score = std::to_string(game.GetScore());
  score += "\n";
  
  //save the user input
  char option;
  
  //check if  user  wants to save their score
  std::cout << "Would you like to add your new score to your saved scores?" << std::endl;
  std::cout << " please type y to save and hit enter, n for no: " << std::endl;
  std::cin >> option;
  
  // if the user types 'y' save score ,otherwise end it
  if(option == 'y')
  {
  Output(score);
  }
  return 0;
}