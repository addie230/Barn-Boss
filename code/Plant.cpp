#include "Plant.h"
#include <stdexcept>

namespace
{
    int getPlantRequiredCycles(int id)
    {
        switch (id)
        {
        case 1:
            return 3;
        case 2:
            return 4;
        default:
            throw std::runtime_error("Invalid seed id.");
        }
    }
    ProductType getPlantProducedProduct(int id)
    {
        switch (id)
        {
        case 1:
            return ProductType::Wheat;
        case 2:
            return ProductType::Corn;
        default:
            throw std::runtime_error("Invalid seed id.");
        }
    }
}

Plant::Plant(int id, int currentCycle)
    : FarmEntity(getPlantRequiredCycles(id),
        getPlantProducedProduct(id),
        currentCycle),
    seedId(id)
{
}

std::string Plant::getName() const
{
    return seedId == 1 ? "Wheat" : "Corn";
}