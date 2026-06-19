#pragma once
#include "Market.h"
#include "TaskBoard.h"
#include "UserManager.h"
#include <string>

class SaveManager
{
public:
    static bool save(const std::string& file, const UserManager& userManager, const Market& market, const TaskBoard& taskBoard);
    static bool load(const std::string& file, UserManager& userManager, Market& market, TaskBoard& taskBoard);
};
