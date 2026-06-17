#pragma once
#include "TaskBoard.h"
#include "User.h"

class TaskManager : public User
{
public:
    TaskManager(int id, const std::string& username, const std::string& password);
    std::string getType() const override;
    void showTasks(const TaskBoard& taskBoard) const;
    bool addTask(TaskBoard& taskBoard, ProductType requiredProduct, int quantity, int rewardBalance, int rewardScore);
    bool removeTask(TaskBoard& taskBoard, int taskId);
};
