#pragma once
#include "FarmEntity.h"

class Animal : public FarmEntity
{
private:
    int animalId{};

public:
    Animal(int id, int currentCycle = 0);
    std::string getName() const override;
    int getKindId() const override 
    { 
        return animalId; 
    }
    char getCategory() const override 
    { 
        return 'A'; 
    }
};
