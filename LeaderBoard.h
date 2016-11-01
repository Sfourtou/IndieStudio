#ifndef GAUNTLET_LEADERBOARD_H
#define GAUNTLET_LEADERBOARD_H


#include <string>
#include <map>

class LeaderBoard {
private:
    std::map<std::string, int> _board;
public:
    LeaderBoard();
    ~LeaderBoard();

    void saveScore();
    void loadScore();
    const std::map<std::string, int> &getBoard() const;
    bool addScore(std::string name, int score);
};


#endif //GAUNTLET_LEADERBOARD_H
