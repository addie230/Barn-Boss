#pragma once
#include "Market.h"
#include "TaskBoard.h"
#include "UserManager.h"
#include <sstream>
#include <string>

class Player;
class MarketManager;
class TaskManager;
class GameEngine
{
private:
    UserManager users;
    Market market;
    TaskBoard tasks;
    User* current = nullptr;
    const std::string saveFile = "save.txt";
    bool running_ = true;
    void handleNoUser(const std::string& cmd, std::istringstream& in);
    void handlePlayerCommand(const std::string& cmd, std::istringstream& in, Player* player);
    void handleMarketManagerCommand(const std::string& cmd, std::istringstream& in, MarketManager* manager);
    void handleTaskManagerCommand(const std::string& cmd, std::istringstream& in, TaskManager* manager);
public:
    void run();
    void execute(const std::string& line);
};