#pragma once
#include "User.h"
#include "MarketManager.h"
#include "Player.h"
#include "TaskManager.h"
#include <memory>
#include <vector>

class UserManager
{
private:
    std::vector<std::unique_ptr<User>> users;
    int nextId = 1;

public:
    bool registerUser(const std::string& username, const std::string& password, const std::string& type);
    User* login(const std::string& username, const std::string& password);
    User* find(const std::string& username) const;
    bool hasType(const std::string& type) const;

    const std::vector<std::unique_ptr<User>>& getUsers() const;
    std::vector<std::unique_ptr<User>>& accessUsers();

    int getNextId() const;
    void setNextId(int nextId);
    void clear();
    void addLoaded(std::unique_ptr<User> user);
};
