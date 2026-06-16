#pragma once
#include "FarmEntity.h"

class Plant : public FarmEntity
{
private:
    int seedId{};

public:
    Plant(int id, int currentCycle = 0);

    std::string getName() const override;
    int getKindId() const override 
    { 
        return seedId; 
    }
    char getCategory() const override 
    { 
        return 'P'; 
    }
};
