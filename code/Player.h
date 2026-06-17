#pragma once
#include "Barn.h"
#include "Farm.h"
#include "Market.h"
#include "TaskBoard.h"
#include "User.h"

class Player : public User
{
private:
    Barn barn;
    Farm farm;
    int balance{ 100 };
    int score{};
    int cycles{};

public:
    Player(int id, std::string username, std::string password);
    std::string getType() const override;
    void profileInfo() const override;
    void nextCycle();

    void checkBalance() const;
    void checkScore() const;
    void checkBarn() const;
    void checkFarm() const;

    bool expandCropland();
    bool expandFarmland();

    bool sowPlant(int seedId);
    bool addAnimal(int animalId);
    bool harvest();

    bool buyItem(Market& market, int productId, int quantity);
    bool sellItem(Market& market, int productId, int quantity);

    bool completeTask(TaskBoard& taskBoard, int taskId);

    int getBalance() const;
    int getScore() const;
    int getCycles() const;

    void setBalance(int value);
    void setScore(int value);
    void setCycles(int value);

    Barn& getBarn();
    Farm& getFarm();

    const Barn& getBarn() const;
    const Farm& getFarm() const;
};