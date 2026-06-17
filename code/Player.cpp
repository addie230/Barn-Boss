#include "Player.h"
#include <iostream>

Player::Player(int id, std::string username, std::string password)
    : User(id, std::move(username), std::move(password))
{
}

std::string Player::getType() const
{
    return "Player";
}

void Player::nextCycle()
{
    ++cycles;
    farm.progress();
}

void Player::profileInfo() const
{
    User::profileInfo();
    std::cout << "Balance: " << balance << '\n' << "Score: " << score << '\n' << "Cycles: " << cycles << '\n';
}

void Player::checkBalance() const
{
    std::cout << "Current Balance: " << balance << '\n';
}

void Player::checkScore() const
{
    std::cout << "Current Score: " << score << '\n';
}

void Player::checkBarn() const
{
    barn.print();
}

void Player::checkFarm() const
{
    farm.print();
}

bool Player::expandCropland()
{
    const int capacity = farm.getCroplandCapacity();
    const int cost = 50 * capacity;
    const int requiredScore = 10 * capacity;
    if (score < requiredScore)
    {
        std::cout << "Cannot expand: score too low.\n";
        return false;
    }
    if (balance < cost)
    {
        std::cout << "Cannot expand: balance too low.\n";
        return false;
    }
    balance -= cost;
    farm.expandCropland();
    nextCycle();
    std::cout << "Cropland expanded successfully!\n";
    return true;
}

bool Player::expandFarmland()
{
    const int capacity = farm.getFarmlandCapacity();
    const int cost = 50 * capacity;
    const int requiredScore = 10 * capacity;
    if (score < requiredScore)
    {
        std::cout << "Cannot expand: score too low.\n";
        return false;
    }
    if (balance < cost)
    {
        std::cout << "Cannot expand: balance too low.\n";
        return false;
    }
    balance -= cost;
    farm.expandFarmland();
    nextCycle();
    std::cout << "Farmland expanded successfully!\n";
    return true;
}

bool Player::sowPlant(int seedId)
{
    if (!farm.sowPlant(seedId, barn))
    {
        return false;
    }
    nextCycle();
    return true;
}

bool Player::addAnimal(int animalId)
{
    if (!farm.addAnimal(animalId, barn))
    {
        return false;
    }
    nextCycle();
    return true;
}

bool Player::harvest()
{
    farm.harvest(barn);
    return true;
}

bool Player::buyItem(Market& market, int productId, int quantity)
{
    const ProductType product = productFromId(productId);
    if (!market.buy(product, quantity, balance))
    {
        return false;
    }
    barn.add(product, quantity);
    nextCycle();
    return true;
}

bool Player::sellItem(Market& market, int productId, int quantity)
{
    const ProductType product = productFromId(productId);
    if (!barn.remove(product, quantity))
    {
        std::cout << "Sale failed: insufficient barn quantity.\n";
        return false;
    }
    if (!market.sell(product, quantity, balance))
    {
        barn.add(product, quantity);
        return false;
    }
    nextCycle();
    return true;
}

bool Player::completeTask(TaskBoard& taskBoard, int taskId)
{
    Task* task = taskBoard.findTask(taskId);
    if (!task)
    {
        std::cout << "Task not found.\n";
        return false;
    }
    if (!barn.remove(task->requiredProduct, task->requiredQuantity))
    {
        std::cout << "Cannot complete task: missing products.\n";
        return false;
    }
    balance += task->rewardBalance;
    score += task->rewardScore;
    taskBoard.eraseTask(taskId);
    nextCycle();
    std::cout << "Task completed successfully!\n";
    return true;
}

int Player::getBalance() const { return balance; }
int Player::getScore() const { return score; }
int Player::getCycles() const { return cycles; }

Barn& Player::getBarn() { return barn; }
Farm& Player::getFarm() { return farm; }
const Barn& Player::getBarn() const { return barn; }
const Farm& Player::getFarm() const { return farm; }

void Player::setBalance(int value) { balance = value; }
void Player::setScore(int value) { score = value; }
void Player::setCycles(int value) { cycles = value; }
