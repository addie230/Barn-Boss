#include "SaveManager.h"
#include "MarketManager.h"
#include "TaskManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace
{
    bool readRequiredLine(std::istream& in, std::string& line, const std::string& expectedPrefix)
    {
        if (!std::getline(in, line))
        {
            return false;
        }
        return line.rfind(expectedPrefix, 0) == 0;
    }
    bool parseProductQuantityToken(const std::string& token, ProductType& product, int& quantity)
    {
        const std::size_t separator = token.find(':');
        if (separator == std::string::npos)
        {
            return false;
        }
        try
        {
            const int productIdValue = std::stoi(token.substr(0, separator));
            quantity = std::stoi(token.substr(separator + 1));
            product = productFromId(productIdValue);
            return true;
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    bool parseEntityToken(const std::string& token, int& id, int& currentCycle)
    {
        const std::size_t separator = token.find(':');
        if (separator == std::string::npos)
        {
            return false;
        }
        try
        {
            id = std::stoi(token.substr(0, separator));
            currentCycle = std::stoi(token.substr(separator + 1));
            return true;
        }
        catch (const std::exception&)
        {
            return false;
        }
    }
}

bool SaveManager::save(const std::string& file, const UserManager& userManager, const Market& market, const TaskBoard& taskBoard)
{
    std::ofstream out(file);
    if (!out)
    {
        return false;
    }
    out << "MARKET\n";
    for (const auto& item : market.getProducts())
    {
        out << productId(item.first) << ' ' << item.second.quantity << ' ' << item.second.price << '\n';
    }
    out << "TASKS\n";
    for (const Task& task : taskBoard.getTasks())
    {
        out << task.id << ' '
            << productId(task.requiredProduct) << ' '
            << task.requiredQuantity << ' '
            << task.rewardBalance << ' '
            << task.rewardScore << '\n';
    }
    out << "USERS\n";
    for (const auto& user : userManager.getUsers())
    {
        out << user->getType() << ' '
            << user->getId() << ' '
            << user->getUsername() << ' '
            << user->getPassword();
        if (const auto* player = dynamic_cast<const Player*>(user.get()))
        {
            out << ' ' << player->getBalance()
                << ' ' << player->getScore()
                << ' ' << player->getCycles()
                << ' ' << player->getFarm().getCroplandCapacity()
                << ' ' << player->getFarm().getFarmlandCapacity();
            out << "\nBARN ";
            for (const auto& item : player->getBarn().getItems())
            {
                out << productId(item.first) << ':' << item.second << ' ';
            }
            out << "\nCROP " << player->getFarm().getCropland().size() << ' ';
            for (const auto& entity : player->getFarm().getCropland())
            {
                out << entity->getKindId() << ':' << entity->getCurrentCycle() << ' ';
            }
            out << "\nLAND " << player->getFarm().getFarmland().size() << ' ';
            for (const auto& entity : player->getFarm().getFarmland())
            {
                out << entity->getKindId() << ':' << entity->getCurrentCycle() << ' ';
            }
        }
        out << "\nENDUSER\n";
    }
    return true;
}

bool SaveManager::load(const std::string& file, UserManager& userManager, Market& market, TaskBoard& taskBoard)
{
    std::ifstream in(file);
    if (!in || in.peek() == std::ifstream::traits_type::eof())
    {
        return false;
    }
    UserManager loadedUsers;
    Market loadedMarket;
    TaskBoard loadedTaskBoard;
    loadedTaskBoard.clear();
    try
    {
        std::string line;
        std::string section;
        while (std::getline(in, line))
        {
            if (line.empty())
            {
                continue;
            }
            if (line == "MARKET" || line == "TASKS" || line == "USERS")
            {
                section = line;
                continue;
            }
            std::istringstream stream(line);
            if (section == "MARKET")
            {
                int id = 0;
                int quantity = 0;
                int price = 0;
                if (!(stream >> id >> quantity >> price))
                {
                    throw std::runtime_error("Invalid MARKET row.");
                }
                loadedMarket.set(productFromId(id), quantity, price);
            }
            else if (section == "TASKS")
            {
                Task task;
                int productIdValue = 0;
                if (!(stream >> task.id >> productIdValue >> task.requiredQuantity >> task.rewardBalance >> task.rewardScore))
                {
                    throw std::runtime_error("Invalid TASKS row.");
                }
                task.requiredProduct = productFromId(productIdValue);
                if (task.id <= 0 || task.requiredQuantity <= 0 || task.rewardBalance < 0 || task.rewardScore < 0)
                {
                    throw std::runtime_error("Invalid task values.");
                }
                loadedTaskBoard.addLoaded(task);
            }
            else if (section == "USERS")
            {
                std::string type;
                std::string username;
                std::string password;
                int id = 0;
                if (!(stream >> type >> id >> username >> password))
                {
                    throw std::runtime_error("Invalid user row.");
                }
                if (id <= 0 || username.empty() || password.size() < 3)
                {
                    throw std::runtime_error("Invalid user values.");
                }
                std::unique_ptr<User> user;
                if (type == "Player")
                {
                    int balance = 0;
                    int score = 0;
                    int cycles = 0;
                    int croplandCapacity = 0;
                    int farmlandCapacity = 0;
                    if (!(stream >> balance >> score >> cycles >> croplandCapacity >> farmlandCapacity))
                    {
                        throw std::runtime_error("Invalid player row.");
                    }
                    auto player = std::make_unique<Player>(id, username, password);
                    player->setBalance(balance);
                    player->setScore(score);
                    player->setCycles(cycles);
                    player->getFarm().setCapacities(croplandCapacity, farmlandCapacity);
                    if (!readRequiredLine(in, line, "BARN "))
                    {
                        throw std::runtime_error("Missing BARN row.");
                    }
                    {
                        std::istringstream barnStream(line);
                        std::string ignored;
                        barnStream >> ignored; 
                        std::string item;
                        while (barnStream >> item)
                        {
                            ProductType product = ProductType::Wheat;
                            int quantity = 0;
                            if (!parseProductQuantityToken(item, product, quantity))
                            {
                                throw std::runtime_error("Invalid barn item.");
                            }
                            player->getBarn().set(product, quantity);
                        }
                    }
                    if (!readRequiredLine(in, line, "CROP "))
                    {
                        throw std::runtime_error("Missing CROP row.");
                    }
                    {
                        std::istringstream cropStream(line);
                        std::string ignored;
                        std::size_t declaredCount = 0;
                        std::size_t loadedCount = 0;
                        cropStream >> ignored >> declaredCount; 
                        std::string item;
                        while (cropStream >> item)
                        {
                            int entityId = 0;
                            int currentCycle = 0;
                            if (!parseEntityToken(item, entityId, currentCycle))
                            {
                                throw std::runtime_error("Invalid crop entity.");
                            }
                            player->getFarm().addLoadedEntity('P', entityId, currentCycle);
                            ++loadedCount;
                        }
                        if (loadedCount != declaredCount)
                        {
                            throw std::runtime_error("CROP count mismatch.");
                        }
                    }
                    if (!readRequiredLine(in, line, "LAND "))
                    {
                        throw std::runtime_error("Missing LAND row.");
                    }
                    {
                        std::istringstream landStream(line);
                        std::string ignored;
                        std::size_t declaredCount = 0;
                        std::size_t loadedCount = 0;
                        landStream >> ignored >> declaredCount; 
                        std::string item;
                        while (landStream >> item)
                        {
                            int entityId = 0;
                            int currentCycle = 0;
                            if (!parseEntityToken(item, entityId, currentCycle))
                            {
                                throw std::runtime_error("Invalid land entity.");
                            }
                            player->getFarm().addLoadedEntity('A', entityId, currentCycle);
                            ++loadedCount;
                        }
                        if (loadedCount != declaredCount)
                        {
                            throw std::runtime_error("LAND count mismatch.");
                        }
                    }
                    user = std::move(player);
                }
                else if (type == "MarketManager")
                {
                    user = std::make_unique<MarketManager>(id, username, password);
                }
                else if (type == "TaskManager")
                {
                    user = std::make_unique<TaskManager>(id, username, password);
                }
                else
                {
                    throw std::runtime_error("Invalid user type.");
                }
                if (user)
                {
                    if (loadedUsers.find(user->getUsername()) != nullptr)
                    {
                        throw std::runtime_error("Duplicate username in save file.");
                    }
                    if ((user->getType() == "MarketManager" || user->getType() == "TaskManager")
                        && loadedUsers.hasType(user->getType()))
                    {
                        throw std::runtime_error("Duplicate manager role in save file.");
                    }
                    loadedUsers.addLoaded(std::move(user));
                }
                if (!readRequiredLine(in, line, "ENDUSER"))
                {
                    throw std::runtime_error("Missing ENDUSER row.");
                }
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Save file could not be loaded: " << e.what() << "\n";
        return false;
    }
    userManager.clear();
    taskBoard.clear();
    market.initDefaults();
    userManager = std::move(loadedUsers);
    market = std::move(loadedMarket);
    taskBoard = std::move(loadedTaskBoard);
    return true;
}