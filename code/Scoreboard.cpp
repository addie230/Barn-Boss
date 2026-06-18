#include "Scoreboard.h"
#include <algorithm>
#include <iostream>
#include <vector>

void Scoreboard::show(const UserManager& userManager)
{
    std::vector<const Player*> players;

    for (const auto& user : userManager.getUsers())
    {
        if (const auto* player = dynamic_cast<const Player*>(user.get()))
        {
            players.push_back(player);
        }
    }

    std::sort(players.begin(), players.end(), [](const Player* left, const Player* right) {
        if (left->getScore() != right->getScore())
        {
            return left->getScore() > right->getScore();
        }

        if (left->getBalance() != right->getBalance())
        {
            return left->getBalance() > right->getBalance();
        }

        return left->getId() < right->getId();
        });

    std::cout << "=== SCOREBOARD ===\n";
    for (std::size_t index = 0; index < players.size(); ++index)
    {
        std::cout << index + 1 << ". " << players[index]->getUsername()
            << " | Score: " << players[index]->getScore()
            << " | Balance: " << players[index]->getBalance() << '\n';
    }
}
