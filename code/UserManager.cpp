#include "UserManager.h"
#include <iostream>

User* UserManager::find(const std::string& username) const
{
    for (const auto& user : users)
    {
        if (user->getUsername() == username)
        {
            return user.get();
        }
    }

    return nullptr;
}

bool UserManager::hasType(const std::string& type) const
{
    for (const auto& user : users)
    {
        if (user->getType() == type)
        {
            return true;
        }
    }

    return false;
}

bool UserManager::registerUser(const std::string& username, const std::string& password, const std::string& type)
{
    if (username.empty() || password.size() < 3)
    {
        std::cout << "Invalid username or password.\n";
        return false;
    }
    if (find(username))
    {
        std::cout << "Username already exists.\n";
        return false;
    }
    if ((type == "MarketManager" || type == "TaskManager") && hasType(type))
    {
        std::cout << "Only one " << type << " is allowed.\n";
        return false;
    }
    if (type == "Player")
    {
        users.push_back(std::make_unique<Player>(nextId++, username, password));
    }
    else if (type == "MarketManager")
    {
        users.push_back(std::make_unique<MarketManager>(nextId++, username, password));
    }
    else if (type == "TaskManager")
    {
        users.push_back(std::make_unique<TaskManager>(nextId++, username, password));
    }
    else
    {
        std::cout << "Invalid user type.\n";
        return false;
    }
    std::cout << "User registered successfully!\n";
    return true;
}

User* UserManager::login(const std::string& username, const std::string& password)
{
    User* user = find(username);
    if (!user || !user->checkPassword(password))
    {
        std::cout << "Invalid username or password.\n";
        return nullptr;
    }
    std::cout << "Welcome, " << username << "!\n";
    return user;
}

const std::vector<std::unique_ptr<User>>& UserManager::getUsers() const
{
    return users;
}

std::vector<std::unique_ptr<User>>& UserManager::accessUsers()
{
    return users;
}

int UserManager::getNextId() const
{
    return nextId;
}

void UserManager::clear()
{
    users.clear();
    nextId = 1;
}

void UserManager::addLoaded(std::unique_ptr<User> user)
{
    if (user->getId() >= nextId)
    {
        nextId = user->getId() + 1;
    }
    users.push_back(std::move(user));
}