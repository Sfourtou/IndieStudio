#include <ios>
#include <fstream>
#include <iostream>
#include "LeaderBoard.h"

LeaderBoard::LeaderBoard() {
}

LeaderBoard::~LeaderBoard() {

}

void	LeaderBoard::saveScore()
{
  std::ofstream file("./gauntlet.score",  std::ios::out | std::ios::trunc);

  if (file.is_open())
    {
        int i = 0;
        for (std::map<std::string, int>::const_iterator it = _board.begin(); it != _board.end() && i < 10; ++it, ++i)
          {
            file << it->first << " " << it->second << std::endl;
          }
        file << "END" << std::endl;
        file.close();
    }
}

bool    LeaderBoard::addScore(std::string name, int score)
{
  _board[name] = score;
}

std::map<std::string, int> const &LeaderBoard::getBoard() const
{
    return _board;
}

void	LeaderBoard::loadScore()
{
  std::ifstream file("./gauntlet.score", std::ios::in);

  if (!file.good() || !file.is_open())
    std::cerr << "Unable to open score file" << std::endl;
    std::string name;
file >> name;
    while (name != "END" && !file.eof())
    {
      int score;
        file >> score;
        std::cout << "COUCOU " << name << std::endl;
        _board[name] = score;
        file >> name;
    }
  file.close();
}
