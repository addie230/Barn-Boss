#include <iostream>
#include <utility>
#include "User.h"

User::User(int id, std::string username, std::string password)
    : id(id)
    , username(std::move(username))
    , password(std::move(password))
{
}

void User::profileInfo() const
{
    std::cout << "ID: " << id << '\n' << "Username: " << username << '\n' << "Type: " << getType() << '\n';
}

void User::logout()
{
    std::cout << "Goodbye, " << username << "!\n";
}

bool User::checkPassword(const std::string& candidatePassword) const
{
    return password == candidatePassword;
}

bool User::changePassword(const std::string& oldPassword, const std::string& newPassword)
{
    if (password != oldPassword || newPassword.size() < 3)
    {
        return false;
    }
    password = newPassword;
    return true;
}

int User::getId() const
{
    return id;
}

const std::string& User::getUsername() const
{
    return username;
}

const std::string& User::getPassword() const
{
    return password;
}