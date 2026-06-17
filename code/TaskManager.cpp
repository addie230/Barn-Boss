#include "TaskManager.h"

TaskManager::TaskManager(int id, const std::string& username, const std::string& password)
    : User(id, username, password)
{
}

std::string TaskManager::getType() const
{
    return "TaskManager";
}

void TaskManager::showTasks(const TaskBoard& taskBoard) const
{
    taskBoard.print();
}

bool TaskManager::addTask(TaskBoard& taskBoard, ProductType requiredProduct, int quantity, int rewardBalance, int rewardScore)
{
    return taskBoard.addTask(requiredProduct, quantity, rewardBalance, rewardScore);
}

bool TaskManager::removeTask(TaskBoard& taskBoard, int taskId)
{
    return taskBoard.removeTask(taskId);
}
