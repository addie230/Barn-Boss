#pragma once
#include "Product.h"
#include <string>

class FarmEntity
{
protected:
    int currentCycle{};
    int requiredCycles{};
    ProductType producedProduct{};

public:
    FarmEntity(int requiredCycles, ProductType producedProduct, int currentCycle = 0)
        : currentCycle(currentCycle)
        , requiredCycles(requiredCycles)
        , producedProduct(producedProduct)
    {}

    virtual ~FarmEntity() = default;
    void progress() 
    { 
        ++currentCycle; 
    }
    bool isReady() const 
    { 
        return currentCycle >= requiredCycles; 
    }

    ProductType getProducedProduct() const 
    { 
        return producedProduct; 
    }
    int getCurrentCycle() const 
    { 
        return currentCycle; 
    }
    int getRequiredCycles() const 
    { 
        return requiredCycles; 
    }

    virtual std::string getName() const = 0;
    virtual int getKindId() const = 0;
    virtual char getCategory() const = 0;
};
