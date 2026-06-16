#pragma once
#include <string>

class User
{
protected:
    int id{};
    std::string username;
    std::string password;

public:
    User(int id, std::string username, std::string password);
    virtual ~User() = default;
    virtual std::string getType() const = 0;
    virtual void profileInfo() const;
    virtual void logout();
    bool checkPassword(const std::string& password) const;
    bool changePassword(const std::string& oldPassword, const std::string& newPassword);
    int getId() const;
    const std::string& getUsername() const;
    const std::string& getPassword() const;
};