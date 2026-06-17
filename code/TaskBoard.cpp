#include "TaskBoard.h"
#include <iostream>

TaskBoard::TaskBoard()
{
    initDefaults();
}

void TaskBoard::initDefaults()
{
    tasks.clear();
    nextId = 1;
    tasks.push_back({ nextId++, ProductType::Wheat, 5, 50, 10 });
    tasks.push_back({ nextId++, ProductType::Milk, 3, 120, 20 });
}

void TaskBoard::print() const
{
    std::cout << "=== TASK BOARD ===\n";
    if (tasks.empty())
    {
        std::cout << "No active tasks.\n";
        return;
    }
    for (const auto& task : tasks)
    {
        std::cout << task.id << ". Deliver "
            << task.requiredQuantity
            << ' '
            << toString(task.requiredProduct)
            << " -> Reward: "
            << task.rewardBalance
            << " Balance, "
            << task.rewardScore
            << " Score\n";
    }
}

bool TaskBoard::addTask(ProductType requiredProduct, int quantity, int rewardBalance, int rewardScore)
{
    if (quantity <= 0 || rewardBalance < 0 || rewardScore < 0)
    {
        return false;
    }
    tasks.push_back(
        {
            nextId++,
            requiredProduct,
            quantity,
            rewardBalance,
            rewardScore
        });
    std::cout << "Task added successfully!\n";
    return true;
}

bool TaskBoard::eraseTask(int taskId)
{
    for (std::size_t i = 0; i < tasks.size(); ++i)
    {
        if (tasks[i].id == taskId)
        {
            tasks.erase(tasks.begin() + static_cast<std::ptrdiff_t>(i));
            return true;
        }
    }
    return false;
}

bool TaskBoard::removeTask(int taskId)
{
    if (!eraseTask(taskId))
    {
        return false;
    }
    std::cout << "Task removed successfully!\n";
    return true;
}

Task* TaskBoard::findTask(int taskId)
{
    for (auto& task : tasks)
    {
        if (task.id == taskId)
        {
            return &task;
        }
    }
    return nullptr;
}

const std::vector<Task>& TaskBoard::getTasks() const
{
    return tasks;
}

int TaskBoard::getNextId() const
{
    return nextId;
}

void TaskBoard::clear()
{
    tasks.clear();
    nextId = 1;
}

void TaskBoard::addLoaded(Task task)
{
    tasks.push_back(task);
    if (task.id >= nextId)
    {
        nextId = task.id + 1;
    }
}