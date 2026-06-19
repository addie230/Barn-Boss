#include "GameEngine.h"
#include "SaveManager.h"
#include "Scoreboard.h"
#include "MarketManager.h"
#include "Player.h"
#include "TaskManager.h"
#include <cstdlib>
#include <iostream>
#include <sstream>

namespace
{
    void banner()
    {
        std::cout << "========================================\n"
            << "            BARN BOSS\n"
            << "========================================\n";
    }
    bool ensureNoExtraInput(std::istringstream& in)
    {
        std::string extra;
        return !(in >> extra);
    }
    bool readArgs(std::istringstream& in, std::string& first, std::string& second)
    {
        return (in >> first >> second) && ensureNoExtraInput(in);
    }
    bool readArgs(std::istringstream& in,
        std::string& first,
        std::string& second,
        std::string& third)
    {
        return (in >> first >> second >> third) && ensureNoExtraInput(in);
    }
    bool readArgs(std::istringstream& in, int& first)
    {
        return (in >> first) && ensureNoExtraInput(in);
    }
    bool readArgs(std::istringstream& in, int& first, int& second)
    {
        return (in >> first >> second) && ensureNoExtraInput(in);
    }
    bool readArgs(std::istringstream& in,
        std::string& first,
        int& second,
        int& third,
        int& fourth)
    {
        return (in >> first >> second >> third >> fourth) && ensureNoExtraInput(in);
    }
}

void GameEngine::run()
{
    if (SaveManager::load(saveFile, users, market, tasks))
    {
        std::cout << "Game loaded successfully.\n";
    }
    else
    {
        std::cout << "New world created.\n";
    }
    banner();
    std::string line;
    while (true)
    {
        std::cout << "> ";
        if (!std::getline(std::cin, line))
        {
            SaveManager::save(saveFile, users, market, tasks);
            std::cout << "\nGame saved successfully.\nGoodbye!\n";
            break;
        }
        try
        {
            execute(line);
        }
        catch (const std::exception& e)
        {
            std::cout << "Error: " << e.what() << '\n';
        }
    }
}

void GameEngine::execute(const std::string& line)
{
    std::istringstream in(line);
    std::string cmd;
    in >> cmd;
    if (cmd.empty())
    {
        return;
    }
    if (cmd == "exit")
    {
        if (!ensureNoExtraInput(in))
        {
            std::cout << "Usage: exit\n";
            return;
        }
        SaveManager::save(saveFile, users, market, tasks);
        std::cout << "Game saved successfully.\nGoodbye!\n";
        std::exit(0);
    }
    if (!current)
    {
        handleNoUser(cmd, in);
        return;
    }
    if (cmd == "logout")
    {
        if (!ensureNoExtraInput(in))
        {
            std::cout << "Usage: logout\n";
            return;
        }
        current->logout();
        current = nullptr;
        banner();
        return;
    }
    if (cmd == "changePassword")
    {
        std::string oldPassword;
        std::string newPassword;
        if (!readArgs(in, oldPassword, newPassword))
        {
            std::cout << "Usage: changePassword <oldPassword> <newPassword>\n";
            return;
        }
        const bool changed = current->changePassword(oldPassword, newPassword);
        std::cout << (changed ? "Password changed successfully!" : "Password change failed.") << '\n';
        return;
    }
    if (cmd == "profileInfo")
    {
        if (!ensureNoExtraInput(in))
        {
            std::cout << "Usage: profileInfo\n";
            return;
        }
        current->profileInfo();
        return;
    }
    if (auto* player = dynamic_cast<Player*>(current))
    {
        handlePlayerCommand(cmd, in, player);
        return;
    }
    if (auto* marketManager = dynamic_cast<MarketManager*>(current))
    {
        handleMarketManagerCommand(cmd, in, marketManager);
        return;
    }
    if (auto* taskManager = dynamic_cast<TaskManager*>(current))
    {
        handleTaskManagerCommand(cmd, in, taskManager);
    }
}

void GameEngine::handleNoUser(const std::string& cmd, std::istringstream& in)
{
    if (cmd == "register")
    {
        std::string username;
        std::string password;
        std::string type;
        if (!readArgs(in, username, password, type))
        {
            std::cout << "Usage: register <username> <password> <Player|MarketManager|TaskManager>\n";
            return;
        }
        users.registerUser(username, password, type);
    }
    else if (cmd == "login")
    {
        std::string username;
        std::string password;
        if (!readArgs(in, username, password))
        {
            std::cout << "Usage: login <username> <password>\n";
            return;
        }
        current = users.login(username, password);
    }
    else
    {
        std::cout << "Please login first.\n";
    }
}

void GameEngine::handlePlayerCommand(const std::string& cmd, std::istringstream& in, Player* player)
{
    if (cmd == "checkBalance")
    {
        if (!ensureNoExtraInput(in))
        {
            std::cout << "Usage: checkBalance\n";
        }
        else
        {
            player->checkBalance();
        }
    }
    else if (cmd == "checkScore")
    {
        if (!ensureNoExtraInput(in))
        {
            std::cout << "Usage: checkScore\n";
        }
        else
        {
            player->checkScore();
        }
    }
    else if (cmd == "checkBarn")
    {
        if (!ensureNoExtraInput(in))
        {
            std::cout << "Usage: checkBarn\n";
        }
        else
        {
            player->checkBarn();
        }
    }
    else if (cmd == "checkFarm")
    {
        if (!ensureNoExtraInput(in))
        {
            std::cout << "Usage: checkFarm\n";
        }
        else
        {
            player->checkFarm();
        }
    }
    else if (cmd == "openMarketCatalog")
    {
        if (!ensureNoExtraInput(in))
        {
            std::cout << "Usage: openMarketCatalog\n";
        }
        else
        {
            market.print();
        }
    }
    else if (cmd == "showTaskBoard")
    {
        if (!ensureNoExtraInput(in))
        {
            std::cout << "Usage: showTaskBoard\n";
        }
        else
        {
            tasks.print();
        }
    }
    else if (cmd == "showScoreboard")
    {
        if (!ensureNoExtraInput(in))
        {
            std::cout << "Usage: showScoreboard\n";
        }
        else
        {
            Scoreboard::show(users);
        }
    }
    else if (cmd == "harvest")
    {
        if (!ensureNoExtraInput(in))
        {
            std::cout << "Usage: harvest\n";
        }
        else
        {
            player->harvest();
        }
    }
    else if (cmd == "buyItem")
    {
        int productId{};
        int quantity{};
        if (!readArgs(in, productId, quantity))
        {
            std::cout << "Usage: buyItem <productId> <quantity>\n";
            return;
        }
        try
        {
            player->buyItem(market, productId, quantity);
        }
        catch (const std::exception&)
        {
            std::cout << "Invalid product id.\n";
        }
    }
    else if (cmd == "sellItem")
    {
        int productId{};
        int quantity{};
        if (!readArgs(in, productId, quantity))
        {
            std::cout << "Usage: sellItem <productId> <quantity>\n";
            return;
        }
        try
        {
            player->sellItem(market, productId, quantity);
        }
        catch (const std::exception&)
        {
            std::cout << "Invalid product id.\n";
        }
    }
    else if (cmd == "sowPlant")
    {
        int seedId{};
        if (!readArgs(in, seedId))
        {
            std::cout << "Usage: sowPlant <1|2>\n";
            return;
        }
        try
        {
            player->sowPlant(seedId);
        }
        catch (const std::exception&)
        {
            std::cout << "Invalid seed id.\n";
        }
    }
    else if (cmd == "addAnimal")
    {
        int animalId{};
        if (!readArgs(in, animalId))
        {
            std::cout << "Usage: addAnimal <3|4>\n";
            return;
        }
        try
        {
            player->addAnimal(animalId);
        }
        catch (const std::exception&)
        {
            std::cout << "Invalid animal id.\n";
        }
    }
    else if (cmd == "expandCropland")
    {
        if (!ensureNoExtraInput(in))
        {
            std::cout << "Usage: expandCropland\n";
        }
        else
        {
            player->expandCropland();
        }
    }
    else if (cmd == "expandFarmland")
    {
        if (!ensureNoExtraInput(in))
        {
            std::cout << "Usage: expandFarmland\n";
        }
        else
        {
            player->expandFarmland();
        }
    }
    else if (cmd == "completeTask")
    {
        int taskId{};
        if (!readArgs(in, taskId))
        {
            std::cout << "Usage: completeTask <taskId>\n";
            return;
        }
        player->completeTask(tasks, taskId);
    }
    else
    {
        std::cout << "Unknown Player command.\n";
    }
}

void GameEngine::handleMarketManagerCommand(const std::string& cmd,
    std::istringstream& in,
    MarketManager* manager)
{
    if (cmd == "openMarketCatalog")
    {
        if (!ensureNoExtraInput(in))
        {
            std::cout << "Usage: openMarketCatalog\n";
        }
        else
        {
            manager->openMarketCatalog(market);
        }
    }
    else if (cmd == "restock")
    {
        int productId{};
        int quantity{};
        if (!readArgs(in, productId, quantity))
        {
            std::cout << "Usage: restock <productId> <quantity>\n";
            return;
        }
        try
        {
            const ProductType product = productFromId(productId);
            manager->restock(market, product, quantity);
        }
        catch (const std::exception&)
        {
            std::cout << "Invalid product id.\n";
        }
    }
    else if (cmd == "changePrice")
    {
        int productId{};
        int newPrice{};
        if (!readArgs(in, productId, newPrice))
        {
            std::cout << "Usage: changePrice <productId> <newPrice>\n";
            return;
        }
        try
        {
            const ProductType product = productFromId(productId);
            manager->changePrice(market, product, newPrice);
        }
        catch (const std::exception&)
        {
            std::cout << "Invalid product id.\n";
        }
    }
    else
    {
        std::cout << "Unknown MarketManager command.\n";
    }
}

void GameEngine::handleTaskManagerCommand(const std::string& cmd,
    std::istringstream& in,
    TaskManager* manager)
{
    if (cmd == "showTasks")
    {
        if (!ensureNoExtraInput(in))
        {
            std::cout << "Usage: showTasks\n";
        }
        else
        {
            manager->showTasks(tasks);
        }
    }
    else if (cmd == "addTask")
    {
        std::string productName;
        int quantity{};
        int rewardBalance{};
        int rewardScore{};
        if (!readArgs(in, productName, quantity, rewardBalance, rewardScore))
        {
            std::cout << "Usage: addTask <productName> <quantity> <rewardBalance> <rewardScore>\n";
            return;
        }
        ProductType product = ProductType::Wheat;
        try
        {
            product = productFromString(productName);
        }
        catch (const std::exception&)
        {
            std::cout << "Invalid product.\n";
            return;
        }
        if (!manager->addTask(tasks, product, quantity, rewardBalance, rewardScore))
        {
            std::cout << "Task add failed.\n";
        }
    }
    else if (cmd == "removeTask")
    {
        int taskId{};
        if (!readArgs(in, taskId))
        {
            std::cout << "Usage: removeTask <taskId>\n";
            return;
        }
        if (!manager->removeTask(tasks, taskId))
        {
            std::cout << "Task not found.\n";
        }
    }
    else
    {
        std::cout << "Unknown TaskManager command.\n";
    }
}