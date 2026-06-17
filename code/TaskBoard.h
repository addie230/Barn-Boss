#pragma once

#include "Task.h"

#include <vector>

class TaskBoard
{
private:
    std::vector<Task> tasks;
    int nextId{ 1 };

public:
    TaskBoard();

    void initDefaults();
    void print() const;

    bool addTask(ProductType requiredProduct, int quantity, int rewardBalance, int rewardScore);
    bool removeTask(int taskId);
    Task* findTask(int taskId);
    bool eraseTask(int taskId);

    const std::vector<Task>& getTasks() const;
    int getNextId() const;

    void clear();
    void addLoaded(Task task);
};