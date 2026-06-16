#pragma once
#include "Barn.h"
#include "FarmEntity.h"
#include <memory>
#include <vector>

class Farm
{
private:
    std::vector<std::unique_ptr<FarmEntity>> cropland;
    std::vector<std::unique_ptr<FarmEntity>> farmland;
    int croplandCapacity{ 3 };
    int farmlandCapacity{ 3 };
public:
    int freeCropland() const;
    int freeFarmland() const;
    int getCroplandCapacity() const;
    int getFarmlandCapacity() const;
    void setCapacities(int newCroplandCapacity, int newFarmlandCapacity);
    bool sowPlant(int seedId, Barn& barn);
    bool addAnimal(int animalId, Barn& barn);
    int harvest(Barn& barn);
    void progress();
    void print() const;
    bool expandCropland();
    bool expandFarmland();
    const std::vector<std::unique_ptr<FarmEntity>>& getCropland() const;
    const std::vector<std::unique_ptr<FarmEntity>>& getFarmland() const;
    void addLoadedEntity(char category, int id, int currentCycle);
};